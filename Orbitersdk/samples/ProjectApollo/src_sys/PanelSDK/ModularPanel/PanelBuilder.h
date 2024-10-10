#pragma once

#include "Panel.h"

#include <string>
#include <vector>

class PanelBuilder {
public:
	static std::vector<Panel> ParsePanelConfig(std::string configPath, bool topLevel = true);

private:
	static void LogErrorMissingPanelKey(std::string configPath, int panelNum, std::string missingKey);
};