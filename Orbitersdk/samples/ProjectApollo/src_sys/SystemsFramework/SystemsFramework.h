#pragma once

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <list>
#include <memory>
#include <optional>
#include <string>

#include "Hydraulic.h"
#include "Electrical.h"
#include "Thermal.h"

constexpr auto SYSTEMSFRAMEWORK_VERSION{ "2.0.0" };

class SystemsFramework {
public:
	std::list<HObject> Hydraulic;
	std::list<EObject> Electrical;
	std::list<TObject> Thermal;

	SystemsFramework(std::string configFilePath);
	void Log(std::string text);
private:
	std::ofstream DebugLog;
};