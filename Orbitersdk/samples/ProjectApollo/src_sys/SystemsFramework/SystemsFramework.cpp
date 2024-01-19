#include "SystemsFramework.h"
#include "Utils.h"

#include <tuple>

enum class SYSTEM_TYPE {
	HYDRAULIC,
	ELECTRIC,
	THERMAL,
	INVALID
};

// Neat trick is to use the last item +1 in the enum for our count
std::string SYSTEM_TYPE_NAMES[(int)SYSTEM_TYPE::INVALID + 1] {"HYDRAULIC", "ELECTRIC", "THERMIC", "INVALID"};

SystemsFramework::SystemsFramework(const std::string configFilePath)
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
		if (trimmed.empty() || trimmed[0] == '#') continue;

		// Hydraulic system
		if (trimmed == "HYDRAULIC") {
			currentSystem = SYSTEM_TYPE::HYDRAULIC;
		}
		else if (trimmed == "THERMIC") {
			currentSystem = SYSTEM_TYPE::THERMAL;
		}
		else if (trimmed == "ELECTRIC") {
			currentSystem = SYSTEM_TYPE::ELECTRIC;
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
			if (trimmed.empty() || trimmed[0] == '#') continue;

			if (trimmed == "/" + SYSTEM_TYPE_NAMES[(int)currentSystem]) break;

			// Read individual objects
			switch (currentSystem) {
			case SYSTEM_TYPE::HYDRAULIC:
				Build_HObject(line, configFile);
				break;
			case SYSTEM_TYPE::THERMAL:
				break;
			case SYSTEM_TYPE::ELECTRIC:
				break;
			default:
				Log("Attempted to read object for invalid system type:" + line);
			}
		}
	}
}

std::tuple<const std::string, std::shared_ptr<HObject>> SystemsFramework::Build_HObject(const std::string firstLine, std::ifstream& configFile)
{
	std::stringstream lineStream{ firstLine };

	char _discard;	// Used for discarding characters like brackets from the input stream

	std::string objectType, name;
	lineStream >> objectType >> name;
	objectType = trim(objectType);

	std::shared_ptr<HObject> objectPtr;

	if (objectType == "PIPE") {
		objectPtr = std::make_shared<HPipe>();
		//TODO
	}
	else if (objectType == "TANK") {
		double x, y, z;
		double vol, isol;
		lineStream >> _discard;
		lineStream >> x >> y >> z;
		lineStream >> _discard;
		lineStream >> vol;
		lineStream >> isol;
		char polarChar = 'D';
		lineStream >> polarChar;

		ThermalPolar polar = ThermalPolar::directional;
		switch (polarChar) {
		case 'D':
			polar = ThermalPolar::directional;
			break;
		case 'C':
			polar = ThermalPolar::cardioid;
			break;
		case 'S':
			polar = ThermalPolar::subcardioid;
			break;
		case 'O':
			polar = ThermalPolar::omni;
			break;
		default:
			polar = ThermalPolar::directional;
		}

		// First, read the substance/chemical information.
		std::string substanceLine;
		std::getline(configFile, substanceLine);
		std::stringstream substanceStream{ substanceLine };
		// TODO: Read substance data

		// Next read the valves and recursively create them via this function.
		std::map<const std::string, std::shared_ptr<HObject>> valves;
		std::string valveLine;
		while (std::getline(configFile, valveLine)) {
			if (valveLine.empty() || valveLine[0] == '#') continue;

			auto valve = Build_HObject(valveLine, configFile);
			// Add them to the map to be put in our tank.
			valves.emplace(std::get<0>(valve), std::get<1>(valve));
			// Add the valves to our hydraulic system map.
			Hydraulic.emplace(std::get<0>(valve), std::get<1>(valve));
		}

		// Finally, return the tank we've created
		objectPtr = std::make_shared<HTank>(x, y, z, vol, isol, polar, valves);
	}
	else if (objectType == "VENT") {
		auto vent = std::make_shared<HVent>();
	}
	else {
		auto object = std::make_shared<HObject>();
	}

	return { name, objectPtr };
}

void SystemsFramework::Log(std::string text)
{
#ifdef _DEBUG
	DebugLog << text << std::endl;
#endif
}