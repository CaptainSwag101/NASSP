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
	virtual void Refresh(double deltaT);
};

class Valve;
class CO2Scrubber : public HObject {
public:
	std::shared_ptr<Valve> valveIn, valveOut;

	CO2Scrubber(std::shared_ptr<Valve> _in, std::shared_ptr<Valve> _out);
};

class HeatExchanger : public HObject {
public:
	HeatExchanger();
};

class H2OSeparator : public HObject {
public:
	std::shared_ptr<Valve> valveIn, valveOut;

	H2OSeparator(std::shared_ptr<Valve> _in, std::shared_ptr<Valve> _out);
};

class Pipe : public HObject {
public:
	std::shared_ptr<Valve> valveIn, valveOut;
	PIPE_DIRECTION direction;

	Pipe(std::shared_ptr<Valve> in, std::shared_ptr<Valve> out, PIPE_DIRECTION dir);
};

class Radiator : public HObject, public TObject {
public:
	Radiator();
};

class Tank;
class Valve : public HObject {
public:
	std::shared_ptr<Tank> parent;
	bool open;
	double size;

	Valve(std::shared_ptr<Tank> _parent, bool _open, double _size);
};

class Tank : public HObject, public TObject {
public:
	double posX, posY, posZ;
	double volume;
	std::map<const std::string, std::shared_ptr<Valve>> valves;

	Tank(double x, double y, double z, double vol, double isol, ThermalPolar polar);
	virtual void Refresh(double deltaT);
};

class Vent : public HObject {
public:
	std::shared_ptr<Valve> valveIn;

	Vent(std::shared_ptr<Valve> in);
};