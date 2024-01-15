#include "SystemsFramework.h"
#include "Utils.h"

SystemsFramework::SystemsFramework(std::string configFilePath)
{
	// If in debug mode, init the log file.
#ifdef _DEBUG
	DebugLog = std::ofstream("ProjectApollo SystemsFramework.log");
#endif

	// Read the systems configuration file and initialize our lists based on its contents.
	std::ifstream configFile{ configFilePath };

	if (!configFile.is_open()) {
		Log("Unable to open config file " + std::string(configFilePath));
		return;
	}

	// Start reading the file
	std::string line;
	std::string trimmed;
	while (std::getline(configFile, line)) {
		// Skip blank lines or comment-only lines
		trimmed = trim(line);
		if (trimmed.empty()) continue;
		if (trimmed[0] == '#') continue;

		// Hydraulic system
		if (trimmed == "HYDRAULIC") {
			// Continue reading lines until we reach the end of the section
			while (std::getline(configFile, line)) {
				// Skip blank lines or comment-only lines
				trimmed = trim(line);
				if (trimmed.empty()) continue;
				if (trimmed[0] == '#') continue;

				if (trimmed == "/HYDRAULIC") break;

				// Read individual objects
				Hydraulic.push_back(Build_HObject(line, configFile));
			}
		}
		// Thermal system
		else if (trimmed == "THERMIC") {
			// Continue reading lines until we reach the end of the section
			while (std::getline(configFile, line)) {
				// Skip blank lines or comment-only lines
				trimmed = trim(line);
				if (trimmed.empty()) continue;
				if (trimmed[0] == '#') continue;

				if (trimmed == "/THERMIC") break;

				// Do stuff here
			}
		}
		// Electrical system
		else if (trimmed == "ELECTRIC") {
			// Continue reading lines until we reach the end of the section
			while (std::getline(configFile, line)) {
				// Skip blank lines or comment-only lines
				trimmed = trim(line);
				if (trimmed.empty()) continue;
				if (trimmed[0] == '#') continue;

				if (trimmed == "/ELECTRIC") break;

				// Do stuff here
			}
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