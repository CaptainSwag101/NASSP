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

HHeatExchanger::HHeatExchanger() {

}

HPipe::HPipe(std::shared_ptr<HValve> in, std::shared_ptr<HValve> out, PIPE_DIRECTION dir)
{
	valveIn = in;
	valveOut = out;
	direction = dir;
}

HRadiator::HRadiator() {

}

HTank::HTank(double x, double y, double z, double vol, double _isol, ThermalPolar _polar, std::map<const std::string, std::shared_ptr<HValve>> vlv)
{
	posX = x;
	posY = y;
	posZ = z;
	volume = vol;
	isolation = _isol;
	polar = _polar;
	valves = vlv;
}

HVent::HVent(std::shared_ptr<HValve> in)
{
	valveIn = in;
}

HValve::HValve()
{
}
