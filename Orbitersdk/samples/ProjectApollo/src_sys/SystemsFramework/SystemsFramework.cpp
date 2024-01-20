#include "SystemsFramework.h"
#include "Utils.h"

#include <tuple>

bool SystemsFramework::logFileInitialized = false;

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
	configFileName = configFilePath;

	// If in debug mode, init the log file.
#ifdef _DEBUG
	InitLog();
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
	while (NextLine(configFile, line)) {
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
		while (NextLine(configFile, line)) {
			// Skip blank lines or comment-only lines
			trimmed = trim(line);
			if (trimmed.empty() || trimmed[0] == '#') continue;
			// End once we reach the terminator of this system block
			if (trimmed == "/" + SYSTEM_TYPE_NAMES[(int)currentSystem]) break;

			// Read individual objects
			switch (currentSystem) {
			case SYSTEM_TYPE::HYDRAULIC:
			{
				auto h_obj = Build_HObject(line, configFile);
				Hydraulic.emplace(std::get<0>(h_obj), std::get<1>(h_obj));
				break;
			}
			case SYSTEM_TYPE::THERMAL:
			{
				// TODO
				break;
			}
			case SYSTEM_TYPE::ELECTRIC:
			{
				// TODO
				break;
			}
			default:
				Log("Attempted to read object for invalid system type:" + line);
			}
		}
	}
}

std::tuple<const std::string, std::shared_ptr<HObject>> SystemsFramework::Build_HObject(const std::string firstLine, std::ifstream& configFile, bool nestedObject)
{
	std::stringstream lineStream{ firstLine };

	char _discard;	// Used for discarding characters like brackets from the input stream

	std::string objectType, name;
	lineStream >> objectType >> name;
	objectType = trim(objectType);

	std::shared_ptr<HObject> objectPtr;

	// Warn when trying to create an object from a block-end tag,
	// this indicates bad parsing code or an invalid config file.
	if (objectType[0] == '/') {
		Log("Attempted to create object from block-end tag, this indicates either a parsing code error or a bad config file!");
	}

	// Fix for unnamed objects
	if (name.empty()) {
		name = "UNNAMED_" + objectType + std::to_string(unnamedObjectCount++);
		Log("Attempted to create object without a name, this is strongly discouraged! Object will be called " + name);
	}

	if (objectType == "CO2SCRUBBER") {
		// TODO
	}
	else if (objectType == "CREW") {
		// TODO
	}
	else if (objectType == "HEATEXCHANGER") {
		// TODO
	}
	else if (objectType == "PIPE") {
		// TODO: Read data

		std::shared_ptr<HValve> in;
		std::shared_ptr<HValve> out;
		PIPE_DIRECTION direction = PIPE_DIRECTION::ONEWAY;
		std::string pipeLine;
		while (NextLine(configFile, pipeLine)) {
			std::string trimmed = trim(pipeLine);
			// Skip blank lines or comment-only lines
			if (trimmed.empty() || trimmed[0] == '#') continue;
			// End once we reach the terminator of this object block
			if (trimmed == "/" + objectType) break;
			std::string valveInName, valveOutName, directionality;
			std::stringstream pipeStream{ pipeLine };

			// Read data
			pipeStream >> valveInName >> valveOutName >> directionality;

			if (directionality == "TWOWAY") {
				direction = PIPE_DIRECTION::TWOWAY;
			}

			// Try and link the valves
			try {
				in = std::static_pointer_cast<HValve>(Hydraulic.at(valveInName));
			}
			catch (std::out_of_range except) {
				Log("Unable to find input valve " + valveInName);
			}

			try {
				out = std::static_pointer_cast<HValve>(Hydraulic.at(valveOutName));
			}
			catch (std::out_of_range except) {
				Log("Unable to find output valve " + valveOutName);
			}
		}

		objectPtr = std::make_shared<HPipe>(in, out, direction);
	}
	else if (objectType == "RADIATOR") {
		// TODO: Read data

		std::string dataLine;
		NextLine(configFile, dataLine);

		// TODO: Read data, part 2

		// Skip terminator line for radiator
		NextLine(configFile, dataLine);

		objectPtr = std::make_shared<HRadiator>();
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
		while (NextLine(configFile, substanceLine)) {
			std::string trimmed = trim(substanceLine);
			// Skip blank lines or comment-only lines
			if (trimmed.empty() || trimmed[0] == '#') continue;

			std::stringstream substanceStream{ substanceLine };
			std::string type;
			substanceStream >> type;
			// Break out if we've moved on to valves
			if (type == "VALVE") break;

			// TODO: Read substance data
		}

		// Next read the valves and recursively create them via this function.
		std::map<const std::string, std::shared_ptr<HValve>> valves;
		std::string valveLine = substanceLine;
		do {
			std::string trimmed = trim(valveLine);
			// Skip blank lines or comment-only lines
			if (trimmed.empty() || trimmed[0] == '#') continue;
			// End once we reach the terminator of this object block
			if (trimmed == "/" + objectType) break;

			auto valve = Build_HObject(valveLine, configFile, true);
			// Add them to the map to be put in our tank.
			valves.emplace(std::get<0>(valve), std::static_pointer_cast<HValve>(std::get<1>(valve)));
			// Add the valves to our hydraulic system map, prefixed with the tank name.
			Hydraulic.emplace(name + ":" + std::get<0>(valve), std::get<1>(valve));
		} while (NextLine(configFile, valveLine));

		// Finally, return the tank we've created
		objectPtr = std::make_shared<HTank>(x, y, z, vol, isol, polar, valves);
	}
	else if (objectType == "VENT") {
		// TODO: Read data

		std::string dataLine;
		NextLine(configFile, dataLine);

		// TODO: Read data, part 2

		// Skip terminator line for vent
		NextLine(configFile, dataLine);

		// Create a dummy valve, TODO fix this!
		auto inValve = std::make_shared<HValve>();
		Hydraulic.emplace(name + ":" + "IN", inValve);

		objectPtr = std::make_shared<HVent>(inValve);
	}
	else if (objectType == "VALVE" || objectType == "EXTVENT") {
		if (!nestedObject) {
			std::string valveLine;
			while (NextLine(configFile, valveLine)) {
				std::string trimmed = trim(valveLine);
				// Skip blank lines or comment-only lines
				if (trimmed.empty() || trimmed[0] == '#') continue;
				// End once we reach the terminator of this object block
				if (trimmed == "/" + objectType) break;
				std::stringstream valveStream{ valveLine };

				// TODO
			}
		}

		objectPtr = std::make_shared<HValve>();
	}
	else {
		// TODO
		Log("Unknown object type " + objectType);
		objectPtr = std::make_shared<HObject>();
	}

	// Fix for unnamed objects

	return { name, objectPtr };
}

void SystemsFramework::InitLog() {
	DebugLog = std::ofstream("ProjectApollo SystemsFramework.log", logFileInitialized ? std::ios::app : std::ios::beg);
	logFileInitialized = true;
}

void SystemsFramework::Log(std::string text)
{
#ifdef _DEBUG
	DebugLog << configFileName << ", line #" << lineNumber << ": " << text << std::endl;
#endif
}

std::istream& SystemsFramework::NextLine(std::istream& stream, std::string& str)
{
	++lineNumber;
	std::getline(stream, str);
	return stream;
}
