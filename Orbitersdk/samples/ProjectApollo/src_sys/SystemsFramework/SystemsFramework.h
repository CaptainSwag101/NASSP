#pragma once

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "Hydraulic.h"
#include "Electrical.h"
#include "Thermal.h"

constexpr auto SYSTEMSFRAMEWORK_VERSION{ "2.0.0" };

class SystemsFramework {
public:
	std::map<std::string, std::shared_ptr<HObject>> Hydraulic;
	std::map<std::string, std::shared_ptr<EObject>> Electrical;
	std::map<std::string, std::shared_ptr<TObject>> Thermal;

	SystemsFramework(std::string configFilePath);
	void Log(std::string text);
private:
	std::ofstream DebugLog;
};