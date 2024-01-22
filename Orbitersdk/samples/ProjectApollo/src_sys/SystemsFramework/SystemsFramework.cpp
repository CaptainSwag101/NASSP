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

	InitLog();

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

std::tuple<const std::string, std::shared_ptr<HObject>> SystemsFramework::Build_HObject(const std::string firstLine, std::ifstream& configFile)
{
	std::stringstream lineStream{ firstLine };

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
		objectPtr = Build_HPipe(objectType, name, lineStream, configFile);
	}
	else if (objectType == "RADIATOR") {
		objectPtr = Build_HRadiator(objectType, name, lineStream, configFile);
	}
	else if (objectType == "TANK") {
		objectPtr = Build_HTank(objectType, name, lineStream, configFile);
	}
	else if (objectType == "VENT" || objectType == "EXTVENT") {
		objectPtr = Build_HVent(objectType, name, lineStream, configFile);
	}
	else if (objectType == "VALVE") {
		objectPtr = Build_HValve(objectType, name, lineStream, configFile, false);
	}
	else {
		// TODO
		Log("Unknown object type " + objectType);
		objectPtr = std::make_shared<HObject>();
	}

	return { name, objectPtr };
}

void SystemsFramework::InitLog() {
	DebugLog = std::ofstream("ProjectApollo SystemsFramework.log", logFileInitialized ? std::ios::app : std::ios::beg);
	logFileInitialized = true;
}

void SystemsFramework::Log(std::string text)
{
	DebugLog << configFileName << ", line #" << lineNumber << ": " << text << std::endl;
}

std::istream& SystemsFramework::NextLine(std::istream& stream, std::string& str)
{
	++lineNumber;
	std::getline(stream, str);
	return stream;
}

std::shared_ptr<HPipe> SystemsFramework::Build_HPipe(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile) {
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

		// Read data
		std::string valveInName, valveOutName, directionality;
		std::stringstream pipeStream{ pipeLine };
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

	return std::make_shared<HPipe>(in, out, direction);
}

std::shared_ptr<HRadiator> SystemsFramework::Build_HRadiator(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile) {
	// TODO: Read data

	std::string dataLine;
	NextLine(configFile, dataLine);

	// TODO: Read data, part 2

	// Skip terminator line for radiator
	NextLine(configFile, dataLine);

	return std::make_shared<HRadiator>();
}

std::shared_ptr<HTank> SystemsFramework::Build_HTank(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile)
{
	// Read tank data.
	char _discard;	// Used for discarding characters like brackets from the input stream
	double x, y, z;
	double vol, isol;
	lineStream >> _discard;
	lineStream >> x >> y >> z;
	lineStream >> _discard;
	lineStream >> vol;
	lineStream >> isol;
	char polarChar = 'D';
	lineStream >> polarChar;

	// Convert polar character to enum value.
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

	// Read the substance/chemical information.
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

	// Create the tank, so we can assign it as a parent to all our valves.
	auto tank = std::make_shared<HTank>(x, y, z, vol, isol, polar);

	// Next read the valves and recursively create them via this function.
	std::map<const std::string, std::shared_ptr<HValve>> valves;
	std::string valveLine = substanceLine;
	do {
		std::string trimmed = trim(valveLine);
		// Skip blank lines or comment-only lines.
		if (trimmed.empty() || trimmed[0] == '#') continue;
		// End once we reach the terminator of this object block.
		if (trimmed == "/" + objectType) break;

		std::stringstream valveStream{ valveLine };
		std::string valveName;
		valveStream >> valveName >> valveName; //Skip "VALVE"
		auto valve = Build_HValve("VALVE", valveName, valveStream, configFile, true);

		// Assign this tank as the valve's parent.
		(*valve).parent = tank;

		// Add them to the map to be put in our tank.
		valves.emplace(valveName, valve);
		// Add the valves to our hydraulic system map, prefixed with the tank name.
		Hydraulic.emplace(name + ":" + valveName, valve);
	} while (NextLine(configFile, valveLine));

	// Assign the valve map to our tank.
	(*tank).valves = valves;

	// Finally, return the tank we've created.
	return tank;
}

std::shared_ptr<HValve> SystemsFramework::Build_HValve(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile, bool nestedObject)
{
	if (nestedObject) {
		bool open;
		double size;
		lineStream >> open >> size;
		return std::make_shared<HValve>(nullptr, open, size);
	}
	else {
		std::string tankName;
		bool open;
		double size;

		std::string line;
		while (NextLine(configFile, line)) {
			std::string trimmed = trim(line);
			// Skip blank lines or comment-only lines
			if (trimmed.empty() || trimmed[0] == '#') continue;
			// End once we reach the terminator of this object block
			if (trimmed == "/" + objectType) break;

			std::stringstream valveStream{ line };
			valveStream >> tankName >> open >> size;
		}

		// Find the HTank object being referenced.
		std::shared_ptr<HTank> tank;
		try {
			tank = std::static_pointer_cast<HTank>(Hydraulic.at(tankName));
		}
		catch (std::out_of_range except) {
			Log("Unable to find parent tank " + tankName);
		}

		return std::make_shared<HValve>(tank, open, size);
	}
}

std::shared_ptr<HVent> SystemsFramework::Build_HVent(const std::string& objectType, const std::string& name, std::stringstream& lineStream, std::ifstream& configFile) {
	// TODO: Read data

	std::string dataLine;
	NextLine(configFile, dataLine);

	// TODO: Read data, part 2

	// Skip terminator line for vent
	NextLine(configFile, dataLine);

	// Create a dummy valve, TODO fix this!
	auto inValve = std::make_shared<HValve>(nullptr, true, 0.0001);
	Hydraulic.emplace(name + ":IN", inValve);

	return std::make_shared<HVent>(inValve);
}
