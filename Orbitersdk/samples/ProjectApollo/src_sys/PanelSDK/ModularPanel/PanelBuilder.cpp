#include "PanelBuilder.h"
#include "OrbiterAPI.h"

#include <toml++/toml.hpp>
#include <fstream>
#include <filesystem>
#include <map>
#include <optional>

std::vector<Panel> PanelBuilder::ParsePanelConfig(std::string configPath)
{
	std::vector<Panel> panels;
	std::map<std::string, int> nameToIndexMap;

	toml::table data = toml::parse_file("Config/ProjectApollo/Panel/" + configPath);

	// Report error if the all-important panels array-of-tables isn't there, or isn't formatted right!
	if (!data["panels"].is_array_of_tables()) {
		oapiWriteLogError("%s %s %s", "Panel config file", configPath.c_str(), "[[panels]] is not present, or is not an array of tables.");
		return panels;
	}

	// Parse the panels from the array of tables.
	if (auto panels_array = data["panels"].as_array()) {
		for (long panelNum = 0; panelNum < panels_array->size(); ++panelNum) {
			toml::table panel_table = *panels_array->at(panelNum).as_table();

			// Read all data for a given panel. Some of these may not exist, either
			// because they are optional or because of a mistake.
			std::optional<std::string> name = panel_table["name"].value<std::string>();
			std::optional<int64_t> width = panel_table["width"].value<int64_t>();
			std::optional<int64_t> height = panel_table["height"].value<int64_t>();
			std::optional<std::string> texture = panel_table["texture"].value<std::string>();
			std::optional<double> fov_override = panel_table["fov_override"].value<double>();
			std::optional<double> offset_x = panel_table["offset_x"].value<double>();
			std::optional<double> offset_y = panel_table["offset_y"].value<double>();
			std::optional<double> offset_z = panel_table["offset_z"].value<double>();

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

			// Finally generate the panel and add it to the vector.
			nameToIndexMap[name.value()] = panels.size();
			panels.emplace_back(name.value(), width.value(), height.value(), texture.value(), fov_override, offset_x, offset_y, offset_z);
		}
	}

	return panels;
}

void PanelBuilder::LogErrorMissingPanelKey(std::string configPath, int panelNum, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has bad panel #%d with missing value '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, missingKey.c_str());
}
