#include "PanelBuilder.h"
#include "OrbiterAPI.h"

#include <cmath>
#include <fstream>
#include <filesystem>
#include <optional>
#include <unordered_map>
#include <toml++/toml.hpp>

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

		panels.emplace_back(info.name.value(), info.width.value(), info.height.value(), info.texture.value(), neighbors, info.camera_direction, info.camera_offset_2d, info.camera_offset_3d, info.camera_rotation_polar, info.camera_rotation_azimuth, info.fov_override);
	}

	return panels;
}

std::vector<PanelInfo> PanelBuilder::ParsePanelInfo(std::string configPath, bool topLevel)
{
	toml::table data;
	// Catch initial TOML syntax and specification violations.
	try {
		data = toml::parse_file(CONFIG_PANEL_PATH + configPath);
	}
	catch (toml::parse_error err) {
		oapiWriteLogError("Panel config file '%s' at line %d column %d: %s", configPath.c_str(), err.source().begin.line, err.source().begin.column, err.description().data());
		return std::vector<PanelInfo>();
	}

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
		auto camera_direction = panel_table["camera_direction"].value<std::string>();
		info.camera_offset_2d.x = panel_table["camera_offset_2d"]["x"].value_or<double>(0.0);
		info.camera_offset_2d.y = panel_table["camera_offset_2d"]["y"].value_or<double>(0.0);
		info.camera_offset_2d.z = panel_table["camera_offset_2d"]["z"].value_or<double>(0.0);
		info.camera_offset_3d.x = panel_table["camera_offset_3d"]["x"].value_or<double>(0.0);
		info.camera_offset_3d.y = panel_table["camera_offset_3d"]["y"].value_or<double>(0.0);
		info.camera_offset_3d.z = panel_table["camera_offset_3d"]["z"].value_or<double>(0.0);
		info.camera_rotation_polar = panel_table["camera_rotation_polar"].value_or<double>(0.0);
		info.camera_rotation_azimuth = panel_table["camera_rotation_azimuth"].value_or<double>(0.0);
		info.fov_override = panel_table["fov_override"].value<double>();

		// Print errors to the log and skip this panel if any of the
		// required pieces of data are missing.
		bool error = false;
		if (!info.name.has_value()) {
			LogErrorMissingPanelData(configPath, panelNum, "name");
			error = true;
		}
		if (!info.width.has_value()) {
			LogErrorMissingPanelData(configPath, panelNum, "width");
			error = true;
		}
		if (!info.height.has_value()) {
			LogErrorMissingPanelData(configPath, panelNum, "height");
			error = true;
		}
		if (!info.texture.has_value()) {
			LogErrorMissingPanelData(configPath, panelNum, "texture");
			error = true;
		}
		else {
			// Make sure the texture exists, so we don't crash by attempting to load
			// a nonexistent texture.
			if (!std::filesystem::exists("Textures/" + Panel2DTexPath(info.texture.value())))
			{
				oapiWriteLogError("Panel config file '%s' has bad panel #%d with a nonexistent texture '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, info.texture.value().c_str());
				error = true;
			}
		}
		if (!camera_direction.has_value()) {
			LogErrorMissingPanelData(configPath, panelNum, "camera_direction");
			error = true;
		}
		else {
			std::unordered_map<std::string, VECTOR3> cameraDirectionMap = {
				{ "forward", { 0.0, 0.0, 1.0 } },	// +X in CSM, +Z in LM
				{ "backward", { 0.0, 0.0, -1.0 } },	// -X in CSM, -Z in LM
				{ "up", { 0.0, 1.0, 0.0 } },		// -Z in CSM, +X in LM
				{ "down", { 0.0, -1.0, 0.0 } },		// +Z in CSM, -X in LM
				{ "left", { -1.0, 0.0, 0.0 } },		// -Y in CSM, -Y in LM
				{ "right", { 1.0, 0.0, 0.0 } },		// +Y in CSM, +Y in LM
				{ "lpd", { 0.0, -sin(30 * RAD), cos(30 * RAD) } },	// Looking forward, 30 degrees down (LM only)
				{ "dynamic", { 0.0, 0.0, 1.0 } },	// Expected to be overridden by vessel code at panel load
			};

			// Check if given direction is valid
			if (cameraDirectionMap.count(camera_direction.value()) > 0) {
				info.camera_direction = cameraDirectionMap[camera_direction.value()];
			}
			else {
				oapiWriteLogError("Panel config file '%s' has bad panel #%d with an invalid camera direction '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, camera_direction.value().c_str());
				error = true;
			}
		}
		// If name exists, check if panel name matches one which is already present in the list
		for (auto& other_info : panelInfo) {
			if (info.name.has_value() && (other_info.name.value() == info.name.value())) {
				oapiWriteLogError("Panel config file '%s' defines multiple panels named '%s', only the first one will be built.", configPath.c_str(), info.name.value().c_str());
				error = true;
				break;
			}
		}
		
		if (error) continue;	// Don't add this panel info to the list if there's critical errors

		// Parse PanelObjectInfo, if it exists
		if (panel_table["objects"].is_array_of_tables()) {
			// Parse the panel object info from the array of tables.
			toml::array object_array = *panel_table["objects"].as_array();
			for (long object_num = 0; object_num < object_array.size(); ++object_num) {
				toml::table object_table = *object_array.at(object_num).as_table();

				// Read all data for a given panel object. Some of these may not exist, either
				// because they are optional or because of a mistake.
				PanelObjectInfo pObjectInfo;

				// If we don't find all the valid data, skip this entry.
				bool error = false;
				if (!object_table["name"].is_string()) {
					LogErrorMissingPanelObjectData(configPath, info.name.value(), object_num, "name");
					error = true;
				}
				if (!object_table["pos2d"]["x"].is_integer()) {
					LogErrorMissingPanelObjectData(configPath, info.name.value(), object_num, "pos2d.x");
					error = true;
				}
				if (!object_table["pos2d"]["y"].is_integer()) {
					LogErrorMissingPanelObjectData(configPath, info.name.value(), object_num, "pos2d.y");
					error = true;
				}
				if (!object_table["texture"].is_string()) {
					LogErrorMissingPanelObjectData(configPath, info.name.value(), object_num, "texture");
					error = true;
				}
				if (error) continue;

				pObjectInfo.Name = object_table["name"].value<std::string>().value();
				pObjectInfo.Pos2D.x = object_table["pos2d"]["x"].value<int>().value();
				pObjectInfo.Pos2D.y = object_table["pos2d"]["y"].value<int>().value();
				pObjectInfo.TextureFilename = object_table["texture"].value<std::string>().value();

				info.objects.push_back(pObjectInfo);
			}
		}

		panelInfo.push_back(info);
	}

	return panelInfo;
}

void PanelBuilder::LogErrorMissingPanelData(std::string configPath, int panelNum, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has bad panel #%d with missing value '%s'. Cannot generate this panel.", configPath.c_str(), panelNum, missingKey.c_str());
}

void PanelBuilder::LogErrorMissingPanelObjectData(std::string configPath, std::string panelName, int pObjectNum, std::string missingKey)
{
	oapiWriteLogError("Panel config file '%s' has panel '%s' with object #%d with missing value '%s'. Skipping this panel object.", configPath.c_str(), panelName.c_str(), pObjectNum, missingKey.c_str());
}

void PanelBuilder::LogErrorMissingPanelNeighbor(std::string configPath, std::string panelName, std::string missingNeighbor)
{
	oapiWriteLogError("Panel config file '%s' has panel '%s' with missing neighbor '%s'.", configPath.c_str(), panelName.c_str(), missingNeighbor.c_str());
}
