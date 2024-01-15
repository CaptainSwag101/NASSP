#pragma once

#include <fstream>

class HObject;
class HPipe;
HObject Build_HObject(std::ifstream& configFile);

class HObject {
public:
	std::string name;

	HObject(std::ifstream& configFile);
};

class HPipe : public HObject {
public:
	HPipe(std::ifstream& configFile);
};

class HTank : public HObject {
public:
	HTank(std::ifstream& configFile);
};

class HVent : public HObject {
public:
	HVent(std::ifstream& configFile);
};