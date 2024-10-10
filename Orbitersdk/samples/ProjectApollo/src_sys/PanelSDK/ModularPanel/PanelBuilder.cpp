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
		if (data["include"].is_array()) {
			auto include_array = data["include"];
			for (long i = 0; i < include_array.as_array()->size(); ++i) {
				auto include_path = include_array[i].as_string()->get();
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
		return includedPanels;
	}

	// Parse the panels from the array of tables.
	toml::array panels_array = *data["panels"].as_array();
	std::vector<Panel> panels(includedPanels);
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

		// Print errors to the log and skip this panel if any of the
		// required pieces of data are missing.
		bool error = false;
		if (!name.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "name");
			error = true;
		}
		if (!width.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "width");
			error = true;
		}
		if (!height.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "height");
			error = true;
		}
		if (!texture.has_value()) {
			LogErrorMissingPanelKey(configPath, panelNum, "texture");
			error = true;
		}
		if (error) continue;

		PanelNeighbors neighbors { neighbor_up, neighbor_down, neighbor_left, neighbor_right };

		// Finally generate the panel and add it to the vector.
		panels.emplace_back(name.value(), width.value(), height.value(), texture.value(), neighbors, fov_override, offset_x, offset_y, offset_z);
	}

	return panels;
}

void PanelBuilder::LogErrorMissingPanelKey(std::string configPath, int panelNum, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has bad panel #%d with missing value '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, missingKey.c_str());
}
