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

class HHeatExchanger : public HObject {
public:
	HHeatExchanger();
};

class HValve;
class HPipe : public HObject {
public:
	std::shared_ptr<HValve> valveIn;
	std::shared_ptr<HValve> valveOut;
	PIPE_DIRECTION direction;

	HPipe(std::shared_ptr<HValve> in, std::shared_ptr<HValve> out, PIPE_DIRECTION dir);
};

class HRadiator : public HObject, public TObject {
public:
	HRadiator();
};

class HTank;
class HValve : public HObject {
public:
	std::shared_ptr<HTank> parent;
	bool open;
	double size;

	HValve(std::shared_ptr<HTank> _parent, bool _open, double _size);
};

class HTank : public HObject, public TObject {
public:
	double posX, posY, posZ;
	double volume;
	std::map<const std::string, std::shared_ptr<HValve>> valves;

	HTank(double x, double y, double z, double vol, double isol, ThermalPolar polar);
	virtual void Refresh(double deltaT);
};

class HVent : public HObject {
public:
	std::shared_ptr<HValve> valveIn;

	HVent(std::shared_ptr<HValve> in);
};