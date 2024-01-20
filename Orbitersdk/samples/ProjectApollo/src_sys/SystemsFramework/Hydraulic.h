#pragma once

#include "Thermal.h"

#include <map>
#include <memory>
#include <string>

enum class SUBSTANCE_TYPE {
	O2,
	H2,
	H2O,
	N2,
	CO2,
	GLYCOL,
	AEROZINE50,
	N2O4,
	He,
};

enum class PIPE_DIRECTION {
	ONEWAY,
	TWOWAY,
};

class HSubstance {
public:
	SUBSTANCE_TYPE type;
	double mass;
	double Q;
	double vapor_mass;

	double p_press;
	double temperature;

	HSubstance(SUBSTANCE_TYPE _type, double _mass, double _q, double _vapor_mass);
};

class HObject {
public:
	HObject();
};

class HHeatExchanger : public HObject {
public:
	HHeatExchanger();
};

class HValve : public HObject {
public:
	HValve();
};

class HRadiator : public HObject {
public:
	HRadiator();
};

class HTank : public HObject, public TObject {
public:
	double posX, posY, posZ;
	double volume;
	std::map<const std::string, std::shared_ptr<HObject>> valves;

	HTank(double x, double y, double z, double vol, double isol, ThermalPolar polar, std::map<const std::string, std::shared_ptr<HObject>> vlv);
};

class HPipe : public HObject {
public:
	std::shared_ptr<HObject> valveIn;
	std::shared_ptr<HObject> valveOut;
	PIPE_DIRECTION direction;

	HPipe(std::shared_ptr<HObject> in, std::shared_ptr<HObject> out, PIPE_DIRECTION dir);
};

class HVent : public HObject {
public:
	HVent();
};