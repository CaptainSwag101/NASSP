#pragma once

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

#include "Generic.h"
#include "Hydraulic.h"
#include "Electrical.h"
#include "Thermal.h"

constexpr auto SYSTEMSFRAMEWORK_VERSION{ "2.0.0" };

class SystemsFramework {
public:
	ShipSystem HydraulicSystem;
	ShipSystem ElectricSystem;
	

	SystemsFramework(const std::string configFile);
	std::tuple<const std::string, std::shared_ptr<HObject>> Build_HObject(const std::string firstLine, std::ifstream& configFile);
	void InitLog();
	void Log(std::string text);
	std::istream& NextLine(std::istream& stream, std::string& str);

private:
	std::ofstream DebugLog;
	std::filesystem::path configFilePath;
	std::filesystem::path logFilePath;
	int64_t unnamedObjectCount = 0;
	int64_t lineNumber = 0;

	std::shared_ptr<CO2Scrubber> Build_CO2Scrubber(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
	std::shared_ptr<H2OSeparator> Build_H2OSeparator(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
	std::shared_ptr<Pipe> Build_Pipe(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
	std::shared_ptr<Radiator> Build_Radiator(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
	std::shared_ptr<Tank> Build_Tank(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
	std::shared_ptr<Valve> Build_Valve(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile, bool nestedObject = false);
	std::shared_ptr<Vent> Build_Vent(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile);
};