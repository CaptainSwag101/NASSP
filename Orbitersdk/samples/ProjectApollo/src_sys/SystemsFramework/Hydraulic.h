#pragma once

#include "Thermal.h"

#include <fstream>
#include <string>

class HObject;
class HPipe;
std::shared_ptr<HObject> Build_HObject(std::string& firstLine, std::ifstream& configFile);

class HObject {
public:
	std::string name;

	HObject(std::stringstream& firstLine, std::ifstream& configFile);
};

class HPipe : public HObject {
public:
	HPipe(std::stringstream& firstLine, std::ifstream& configFile);
};

class HTank : public HObject, public TObject {
public:
	double posX, posY, posZ;
	double volume;

	HTank(std::stringstream& firstLine, std::ifstream& configFile);
};

class HVent : public HObject {
public:
	HVent(std::stringstream& firstLine, std::ifstream& configFile);
};