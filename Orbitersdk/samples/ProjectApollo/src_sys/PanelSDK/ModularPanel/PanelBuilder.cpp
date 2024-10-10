#include "PanelBuilder.h"
#include "OrbiterAPI.h"

#include <toml++/toml.hpp>
#include <fstream>
#include <filesystem>
#include <optional>
#include <unordered_map>

const static std::string CONFIG_PANEL_PATH = "Config/ProjectApollo/Panel/";

std::vector<Panel> PanelBuilder::ParsePanelConfig(std::string configPath, bool topLevel)
{
	toml::table data = toml::parse_file(CONFIG_PANEL_PATH + configPath);

	// Parse the [include] table at the start of the file, but only if this is the top-level config!
	// We do not allow nesting beyond one layer, for simplicity's sake.
	std::vector<Panel> includedPanels;
	if (topLevel) {
		if (auto include_array = data["include"].as_array()) {
			for (long i = 0; i < include_array->size(); ++i) {
				std::string include_path = *include_array[i].value<std::string>();
				// Skip if the file doesn't actually exist.
				if (!std::filesystem::exists(CONFIG_PANEL_PATH + include_path)) {
					oapiWriteLogError("Panel config file '%s' includes file '%s' which does not exist. It will be skipped.", configPath.c_str(), include_path.c_str());
					continue;
				}

				auto temp = ParsePanelConfig(include_path, false);
				includedPanels.insert(includedPanels.end(), temp.begin(), temp.end());
			}
		}
	}

	// Report error if the all-important panels array-of-tables isn't there, or isn't formatted right!
	if (!data["panels"].is_array_of_tables()) {
		oapiWriteLogError("Panel config file '%s' [[panels]] array is not present, or is not an array of tables.", configPath.c_str());
		return std::vector<Panel>();
	}

	// Parse the panels from the array of tables.
	
	// Pass 1: Read only the panel names. Add them to a map so we can reference them by index later.
	toml::array panels_array = *data["panels"].as_array();
	std::vector<Panel> panels(panels_array.size());	// Allocate enough space right away, for better performance
	std::unordered_map<std::string, int> nameIndexMap;
	for (auto& array_item : panels_array) {
		toml::table panel_table = *array_item.as_table();
		auto name = panel_table["name"].value<std::string>();

		// Skip the panel if it has no name. We'll log this error during pass 2.
		if (!name.has_value()) {
			continue;
		}

		nameIndexMap[name.value()] = nameIndexMap.size();
	}

	// Pass 2: Parse all the data, and associate neighbor panel names with their index.
	for (long panelNum = 0; panelNum < panels_array.size(); ++panelNum) {
		toml::table panel_table = *panels_array.at(panelNum).as_table();

		// Read all data for a given panel. Some of these may not exist, either
		// because they are optional or because of a mistake.
		auto name = panel_table["name"].value<std::string>();
		auto width = panel_table["width"].value<int64_t>();
		auto height = panel_table["height"].value<int64_t>();
		auto texture = panel_table["texture"].value<std::string>();
		auto neighbor_up = panel_table["neighbor"]["up"].value<std::string>();
		auto neighbor_down = panel_table["neighbor"]["down"].value<std::string>();
		auto neighbor_left = panel_table["neighbor"]["left"].value<std::string>();
		auto neighbor_right = panel_table["neighbor"]["right"].value<std::string>();
		auto fov_override = panel_table["fov_override"].value<double>();
		auto offset_x = panel_table["offset_x"].value<double>();
		auto offset_y = panel_table["offset_y"].value<double>();
		auto offset_z = panel_table["offset_z"].value<double>();

		// Print an error to the log and skip this panel if any of the
		// required pieces of data are missing.
		if (!name.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "name");
			continue;
		}
		if (!width.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "width");
			continue;
		}
		if (!height.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "height");
			continue;
		}
		if (!texture.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "texture");
			continue;
		}

		// Find the indices for all the panels, if they exist.
		std::optional<int> index_up, index_down, index_left, index_right;
		if (neighbor_up.has_value() && nameIndexMap.count(neighbor_up.value()) > 0)
			index_up = nameIndexMap.at(neighbor_up.value());
		if (neighbor_down.has_value() && nameIndexMap.count(neighbor_down.value()) > 0)
			index_down = nameIndexMap.at(neighbor_down.value());
		if (neighbor_left.has_value() && nameIndexMap.count(neighbor_left.value()) > 0)
			index_left = nameIndexMap.at(neighbor_left.value());
		if (neighbor_right.has_value() && nameIndexMap.count(neighbor_right.value()) > 0)
			index_right = nameIndexMap.at(neighbor_right.value());

		PanelNeighbors neighbors { index_up, index_down, index_left, index_right };

		// Finally generate the panel and add it to the vector.
		panels.emplace_back(name.value(), width.value(), height.value(), texture.value(), neighbors, fov_override, offset_x, offset_y, offset_z);
	}

	return panels;
}

void PanelBuilder::LogErrorMissingPanelKey(std::string configPath, int panelNum, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has bad panel #%d with missing value '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, missingKey.c_str());
}
