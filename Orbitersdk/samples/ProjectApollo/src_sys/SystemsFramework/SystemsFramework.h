#pragma once

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>

#include "Hydraulic.h"
#include "Electrical.h"
#include "Thermal.h"

constexpr auto SYSTEMSFRAMEWORK_VERSION{ "2.0.0" };

class SystemsFramework {
public:
	std::map<const std::string, std::shared_ptr<HObject>> Hydraulic;
	std::map<const std::string, std::shared_ptr<EObject>> Electrical;
	std::map<const std::string, std::shared_ptr<TObject>> Thermal;

	SystemsFramework(const std::string configFilePath);
	std::tuple<const std::string, std::shared_ptr<HObject>> Build_HObject(const std::string firstLine, std::ifstream& configFile, bool nestedObject = false);
	void Log(std::string text);
	std::istream& NextLine(std::istream& stream, std::string& str);
private:
	std::ofstream DebugLog;
	std::string configFileName;
	int64_t unnamedObjectCount = 0;
	int64_t lineNumber = 0;
};