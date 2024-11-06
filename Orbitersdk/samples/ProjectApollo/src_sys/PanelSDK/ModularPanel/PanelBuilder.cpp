#include "PanelBuilder.h"
#include "OrbiterAPI.h"

#include <toml++/toml.hpp>
#include <fstream>
#include <filesystem>
#include <optional>
#include <unordered_map>

const static std::string CONFIG_PANEL_PATH = "Config/ProjectApollo/Panel/";

std::vector<Panel> PanelBuilder::LoadFromConfigFile(std::string configPath) {
	// Phase 1: Load all the data from the config file, ensuring no crucial data is missing,
	// also checking to ensure no duplicates exist.
	auto panelInfo = ParsePanelInfo(configPath, true);

	// Phase 2: Create Panel objects from panel info structs
	auto panels = PanelInfoToObjects(configPath, panelInfo);

	return panels;
}

std::vector<Panel> PanelBuilder::PanelInfoToObjects(std::string configPath, std::vector<PanelInfo>& panelInfo) {
	std::vector<Panel> panels;
	std::unordered_map<std::string, int> panelNameMap;	// Map for performant matching of panel name to index
	// Pre-allocate space for better performance
	panels.reserve(panelInfo.size());
	panelNameMap.reserve(panelInfo.size());

	// Populate map with name-index pairs
	for (auto& info : panelInfo) {
		panelNameMap[info.name.value()] = panelNameMap.size();
	}

	// Assign neighbor indices and create Panel objects
	for (auto& info : panelInfo) {
		PanelNeighbors neighbors;
		if (info.neighbor_up.has_value())
			if (panelNameMap.count(info.neighbor_up.value()) > 0)
				neighbors.Up = panelNameMap[info.neighbor_up.value()];
			else
				LogErrorMissingPanelNeighbor(configPath, info.name.value(), info.neighbor_up.value());
		if (info.neighbor_down.has_value())
			if (panelNameMap.count(info.neighbor_down.value()) > 0)
				neighbors.Down = panelNameMap[info.neighbor_down.value()];
			else
				LogErrorMissingPanelNeighbor(configPath, info.name.value(), info.neighbor_down.value());
		if (info.neighbor_left.has_value())
			if (panelNameMap.count(info.neighbor_left.value()) > 0)
				neighbors.Left = panelNameMap[info.neighbor_left.value()];
			else
				LogErrorMissingPanelNeighbor(configPath, info.name.value(), info.neighbor_left.value());
		if (info.neighbor_right.has_value())
			if (panelNameMap.count(info.neighbor_right.value()) > 0)
				neighbors.Right = panelNameMap[info.neighbor_right.value()];
			else
				LogErrorMissingPanelNeighbor(configPath, info.name.value(), info.neighbor_right.value());

		panels.emplace_back(info.name.value(), info.width.value(), info.height.value(), info.texture.value(), neighbors, info.fov_override, info.offset_x, info.offset_y, info.offset_z);
	}

	return panels;
}

std::vector<PanelInfo> PanelBuilder::ParsePanelInfo(std::string configPath, bool topLevel)
{
	toml::table data = toml::parse_file(CONFIG_PANEL_PATH + configPath);

	// Parse the [include] table at the start of the file, but only if this is the top-level config!
	// We do not allow nesting beyond one layer, for simplicity's sake.
	std::vector<PanelInfo> panelInfo;
	if (topLevel) {
		if (data["include"].is_array()) {
			auto include_array = data["include"];
			for (long i = 0; i < include_array.as_array()->size(); ++i) {
				auto& include_path = include_array[i].as_string()->get();
				// Skip if the file doesn't actually exist.
				if (!std::filesystem::exists(CONFIG_PANEL_PATH + include_path)) {
					oapiWriteLogError("Panel config file '%s' includes file '%s' which does not exist. It will be skipped.", configPath.c_str(), include_path.c_str());
					continue;
				}

				auto temp = ParsePanelInfo(include_path, false);
				panelInfo.insert(panelInfo.end(), temp.begin(), temp.end());
			}
		}
	}

	// Report error if the all-important panels array-of-tables isn't there, or isn't formatted right!
	if (!data["panels"].is_array_of_tables()) {
		oapiWriteLogError("Panel config file '%s' [[panels]] array is not present, or is not an array of tables.", configPath.c_str());
		return panelInfo;
	}

	// Parse the panels from the array of tables.
	toml::array panels_array = *data["panels"].as_array();
	for (long panelNum = 0; panelNum < panels_array.size(); ++panelNum) {
		toml::table panel_table = *panels_array.at(panelNum).as_table();

		// Read all data for a given panel. Some of these may not exist, either
		// because they are optional or because of a mistake.
		PanelInfo info;
		info.name = panel_table["name"].value<std::string>();
		info.width = panel_table["width"].value<int64_t>();
		info.height = panel_table["height"].value<int64_t>();
		info.texture = panel_table["texture"].value<std::string>();
		info.neighbor_up = panel_table["neighbor"]["up"].value<std::string>();
		info.neighbor_down = panel_table["neighbor"]["down"].value<std::string>();
		info.neighbor_left = panel_table["neighbor"]["left"].value<std::string>();
		info.neighbor_right = panel_table["neighbor"]["right"].value<std::string>();
		info.fov_override = panel_table["fov_override"].value<double>();
		info.offset_x = panel_table["offset_x"].value<double>();
		info.offset_y = panel_table["offset_y"].value<double>();
		info.offset_z = panel_table["offset_z"].value<double>();

		// Print errors to the log and skip this panel if any of the
		// required pieces of data are missing.
		bool error = false;
		if (!info.name.has_value()) {
			LogErrorMissingPanelData(configPath, panelNum, "name");
			error = true;
		}
		else {
			// If name exists, check if panel name matches one which is already present in the list
			for (auto& other_info : panelInfo) {
				if (other_info.name.value() == info.name.value()) {
					oapiWriteLogError("Panel config file '%s' defines multiple panels named '%s', only the first one will be built.", configPath.c_str(), info.name.value().c_str());
					error = true;
					break;
				}
			}
		}

		if (!info.width.has_value()) {
			LogErrorMissingPanelData(configPath, info.name.value(), "width");
			error = true;
		}
		if (!info.height.has_value()) {
			LogErrorMissingPanelData(configPath, info.name.value(), "height");
			error = true;
		}
		if (!info.texture.has_value()) {
			LogErrorMissingPanelData(configPath, info.name.value(), "texture");
			error = true;
		}
		
		if (error) continue;

		panelInfo.push_back(info);
	}

	return panelInfo;
}

void PanelBuilder::LogErrorMissingPanelData(std::string configPath, int panelNum, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has bad panel #%d with missing value '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, missingKey.c_str());
}

void PanelBuilder::LogErrorMissingPanelData(std::string configPath, std::string panelName, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has bad panel '%s' with missing value '%s'. Cannot generate this panel.", configPath.c_str(), panelName.c_str(), missingKey.c_str());
}

void PanelBuilder::LogErrorMissingPanelNeighbor(std::string configPath, std::string panelName, std::string missingNeighbor)
{
	oapiWriteLogError("Panel config file '%s' has panel '%s' with missing neighbor '%s'.", configPath.c_str(), panelName.c_str(), missingNeighbor.c_str());
}
