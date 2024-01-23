#include "Hydraulic.h"
#include "Utils.h"


HSubstance::HSubstance(SUBSTANCE_TYPE _type, double _mass, double _q, double _vapor_mass)
{
	type = _type;
	mass = _mass;
	Q = _q;
	vapor_mass = _vapor_mass;
}

HObject::HObject()
{
    
}

void HObject::Refresh(double deltaT)
{
}

CO2Scrubber::CO2Scrubber(std::shared_ptr<Valve> _in, std::shared_ptr<Valve> _out)
{
	valveIn = _in;
	valveOut = _out;
}

HeatExchanger::HeatExchanger() {

}

H2OSeparator::H2OSeparator(std::shared_ptr<Valve> _in, std::shared_ptr<Valve> _out)
{
	valveIn = _in;
	valveOut = _out;
}

Pipe::Pipe(std::shared_ptr<Valve> in, std::shared_ptr<Valve> out, PIPE_DIRECTION dir)
{
	valveIn = in;
	valveOut = out;
	direction = dir;
}

Radiator::Radiator() {

}

Tank::Tank(double x, double y, double z, double vol, double _isol, ThermalPolar _polar)
{
	posX = x;
	posY = y;
	posZ = z;
	volume = vol;
	isolation = _isol;
	polar = _polar;
}

void Tank::Refresh(double deltaT)
{

}

Vent::Vent(std::shared_ptr<Valve> in)
{
	valveIn = in;
}

Valve::Valve(std::shared_ptr<Tank> _parent, bool _open, double _size)
{
	parent = _parent;
	open = _open;
	size = _size;
}
