#include "SystemsFramework.h"
#include "Utils.h"

enum class SYSTEM_TYPE {
	HYDRAULIC,
	ELECTRIC,
	THERMAL,
	INVALID
};

// Neat trick is to use the last item +1 in the enum for our count
std::string SYSTEM_NAMES[(int)SYSTEM_TYPE::INVALID + 1] {"HYDRAULIC", "ELECTRIC", "THERMIC", "INVALID"};

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
	SYSTEM_TYPE currentSystem = SYSTEM_TYPE::INVALID;
	while (std::getline(configFile, line)) {
		// Skip blank lines or comment-only lines
		trimmed = trim(line);
		if (trimmed.empty()) continue;
		if (trimmed[0] == '#') continue;

		// Hydraulic system
		if (trimmed == "HYDRAULIC") {
			currentSystem = SYSTEM_TYPE::HYDRAULIC;
		}
		else if (trimmed == "THERMIC") {
			currentSystem = SYSTEM_TYPE::ELECTRIC;
		}
		else if (trimmed == "ELECTRIC") {
			currentSystem = SYSTEM_TYPE::THERMAL;
		}
		// Invalid
		else {
			Log("Invalid system category " + line);
			currentSystem = SYSTEM_TYPE::INVALID;
			continue;
		}

		// Continue reading lines until we reach the end of the section
		while (std::getline(configFile, line)) {
			// Skip blank lines or comment-only lines
			trimmed = trim(line);
			if (trimmed.empty()) continue;
			if (trimmed[0] == '#') continue;

			if (trimmed == "/" + SYSTEM_NAMES[(int)currentSystem]) break;

			// Read individual objects
			
		}
	}
}

void SystemsFramework::Log(std::string text)
{
#ifdef _DEBUG
	DebugLog << text << std::endl;
#endif
}