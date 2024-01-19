#include "Hydraulic.h"
#include "Utils.h"


HSubstance::HSubstance(SUBSTANCE_TYPE _type, double _mass, double _q, double _vapor_mass)
{

}

HObject::HObject()
{
    
}

HPipe::HPipe()
{

}

HTank::HTank(double x, double y, double z, double vol, double _isol, ThermalPolar _polar, std::map<const std::string, std::shared_ptr<HObject>> vlv)
{
	posX = x;
	posY = y;
	posZ = z;
	volume = vol;
	isolation = _isol;
	polar = _polar;
	valves = vlv;
}

HVent::HVent()
{

}
