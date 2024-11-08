#pragma once

#include "Panel.h"

#include <string>
#include <vector>

struct PanelInfo {
	std::optional<std::string> name, texture;
	std::optional<int> width, height;
	std::optional<std::string> neighbor_up, neighbor_down, neighbor_left, neighbor_right;
	VECTOR3 camera_direction, camera_offset_2d, camera_offset_3d;
	double camera_rotation_polar, camera_rotation_azimuth;
	std::optional<double> fov_override;
	std::vector<PanelObjectInfo> objects;
};

class PanelBuilder {
public:
	static std::vector<Panel> LoadFromConfigFile(std::string configPath);

private:
	static std::vector<Panel> PanelInfoToObjects(std::string configPath, std::vector<PanelInfo>& info);
	static std::vector<PanelInfo> ParsePanelInfo(std::string configPath, bool topLevel);
	static void LogErrorMissingPanelData(std::string configPath, int panelNum, std::string missingKey);
	static void LogErrorMissingPanelObjectData(std::string configPath, std::string panelName, int pObjectNum, std::string missingKey);
	static void LogErrorMissingPanelNeighbor(std::string configPath, std::string panelName, std::string missingNeighbor);
};