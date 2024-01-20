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
	std::map<const std::string, std::shared_ptr<HVent>> Hydraulic_Vents;
	std::map<const std::string, std::shared_ptr<EObject>> Electrical;
	std::map<const std::string, std::shared_ptr<TObject>> Thermal;

	SystemsFramework(const std::string configFilePath);
	std::tuple<const std::string, std::shared_ptr<HObject>> Build_HObject(const std::string firstLine, std::ifstream& configFile);
	void InitLog();
	void Log(std::string text);
	std::istream& NextLine(std::istream& stream, std::string& str);

private:
	std::ofstream DebugLog;
	std::string configFileName;
	static bool logFileInitialized;
	int64_t unnamedObjectCount = 0;
	int64_t lineNumber = 0;

	std::shared_ptr<HTank> Build_HTank(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
	std::shared_ptr<HValve> Build_HValve(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile, bool nestedObject = false);
};