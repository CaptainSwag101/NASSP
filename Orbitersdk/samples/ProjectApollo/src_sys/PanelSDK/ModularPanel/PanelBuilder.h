#pragma once

#include "Panel.h"

#include <string>
#include <vector>

struct PanelInfo {
	std::optional<std::string> name, texture;
	std::optional<int> width, height;
	PanelNeighbors neighbors;
	std::optional<double> fov_override, offset_x, offset_y, offset_z;
};

class PanelBuilder {
public:
	static std::vector<Panel> LoadFromConfigFile(std::string configPath);

private:
	static std::vector<Panel> PanelInfoToObjects(std::string configPath, std::vector<PanelInfo>& info);
	static std::vector<PanelInfo> ParsePanelInfo(std::string configPath, bool topLevel);
	static void LogErrorMissingPanelKey(std::string configPath, int panelNum, std::string missingKey);
};