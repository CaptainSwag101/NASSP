#include "Hydraulic.h"
#include "Utils.h"

#include <fstream>
#include <memory>
#include <sstream>
#include <string>

std::shared_ptr<HObject> Build_HObject(std::string& firstLine, std::ifstream& configFile)
{
	std::stringstream lineStream{ firstLine };

	std::string objectType;
	lineStream >> objectType;
	objectType = trim(objectType);
	if (objectType == "PIPE") {
		return std::make_shared<HPipe>(lineStream, configFile);
	}
	else if (objectType == "TANK") {
		return  std::make_shared<HTank>(lineStream, configFile);
	}
	else if (objectType == "VENT") {
		return  std::make_shared<HVent>(lineStream, configFile);
	}
	else {
		return  std::make_shared<HObject>(lineStream, configFile);
	}
}

HObject::HObject(std::stringstream& firstLine, std::ifstream& configFile)
{
    firstLine >> name;
}

HPipe::HPipe(std::stringstream& firstLine, std::ifstream& configFile) : HObject(firstLine, configFile)
{

}

HTank::HTank(std::stringstream& firstLine, std::ifstream& configFile) : HObject(firstLine, configFile)
{
	char _discard;
	firstLine >> _discard;
	firstLine >> posX >> posY >> posZ;
	firstLine >> _discard;
	firstLine >> volume;
	firstLine >> isolation;
	char polarChar = 'D';
	firstLine >> polarChar;

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

	// Now, we need to read in the data attached to the tank: namely the chemical inside and the valves.
	std::string line;
	while (std::getline(configFile, line)) {

	}
}

HVent::HVent(std::stringstream& firstLine, std::ifstream& configFile) : HObject(firstLine, configFile)
{

}
