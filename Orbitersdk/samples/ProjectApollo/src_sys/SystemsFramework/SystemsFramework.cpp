#include "SystemsFramework.h"

SystemsFramework::SystemsFramework(std::string configFilePath)
{
	// If in debug mode, init the log file.
#ifdef _DEBUG
	DebugLog = std::ofstream("ProjectApollo SystemsFramework.log");
#endif

	// Read the systems configuration file and initialize our lists based on its contents.
	std::ifstream configFile{ std::string("Config/ProjectApollo/" + configFilePath + ".cfg")};

	if (!configFile.is_open()) {
		Log("Unable to open config file " + std::string(configFilePath));
		return;
	}

	// Start reading the file
	std::string line;
	while (std::getline(configFile, line)) {
		// Hydraulic system
		if (line == "<HYDRAULIC>") {
			// Continue reading lines until we reach the end of hydralic delcaration
			while (line != "</HYDRAULIC>") {
				// Read individual objects
				std::string objectType;
				configFile >> objectType;
				if (objectType == "<PIPE>") {
					Hydraulic.push_back(HPipe(configFile));
				}
				else if (objectType == "<TANK>") {
					Hydraulic.push_back(HTank(configFile));
				}
				else if (objectType == "<VENT>") {
					Hydraulic.push_back(HVent(configFile));
				}
				else {
					Hydraulic.push_back(HObject(configFile));
				}
			}
		}
		// Thermal system
		else if (line == "<THERMIC>") {

		}
		// Electrical system
		else if (line == "<ELECTRIC>") {

		}
		// Invalid
		else {
			Log("Invalid system category " + line);
		}
	}
}

void SystemsFramework::Log(std::string text)
{
#ifdef _DEBUG
	DebugLog << text << std::endl;
#endif
}
