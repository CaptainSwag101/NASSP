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

}

HVent::HVent(std::stringstream& firstLine, std::ifstream& configFile) : HObject(firstLine, configFile)
{

}
