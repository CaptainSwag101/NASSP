#include "PanelBuilder.h"
#include "OrbiterAPI.h"

#include <toml.hpp>
#include <fstream>
#include <filesystem>

std::vector<Panel> PanelBuilder::ParsePanelConfig(std::string configPath)
{
	std::vector<Panel> panels;

	auto data = toml::parse("Config/ProjectApollo/Panel/" + configPath);

	// Report error if the all-important panels array-of-tables isn't there, or isn't formatted right!
	if (!data.at("panels").is_array_of_tables()) {
		oapiWriteLogError("%s %s %s", "Panel config file", configPath.c_str(), "[[panels]] is not present, or is not an array of tables.");
		return panels;
	}

	// Parse the panels from the array of tables
	auto panels_array = data.at("panels").as_array();
	for (auto& panel_value : panels_array) {
		std::string name = toml::find_or<std::string>(panel_value, "name", "UNNAMED");
	}

	return panels;
}
