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
		
	}
}

void SystemsFramework::Log(std::string text)
{
#ifdef _DEBUG
	DebugLog << text << std::endl;
#endif
}
