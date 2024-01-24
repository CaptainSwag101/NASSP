#include "Hydraulic.h"
#include "Utils.h"
//#include "../PanelSDK/Internals/Hsystems.h"


HSubstance::HSubstance(SUBSTANCE_TYPE _type, double _mass, double _q, double _vapor_mass)
{
	type = _type;
	mass = _mass;
	Q = _q;
	vapor_mass = _vapor_mass;
}

void HSubstance::operator+=(HSubstance add)
{
	if (type == add.type) {
		mass += add.mass;
		Q += add.Q;
		vapor_mass += add.vapor_mass;
	}
}

void HSubstance::operator-=(HSubstance sub)
{
	if (type == sub.type) {
		mass -= sub.mass;
		Q -= sub.Q;
		vapor_mass -= sub.vapor_mass;
	}
}

double HSubstance::VAPENTH() const
{
	const int subst_type = (int)type;

	if (temperature > CRITICAL_T[subst_type] || temperature <= 0.0) return 0.0;

	return (R_CONST / 1000 * CRITICAL_T[subst_type] *
		(7.08 * pow((1 - temperature / CRITICAL_T[subst_type]), 0.354) +
			10.95 * ACENTRIC[subst_type] * pow((1 - temperature / CRITICAL_T[subst_type]), 0.456))) / MMASS[subst_type]; //[1]

	//[1] [29] G.F. Carruth, R. Kobayashi, Extension to low reduced temperatures of three-parameter corresponding states: vapor pressures,
	//enthalpies and entropies of vaporization, and liquid fugacity coefficients, Industrial & Engineering Chemistry Fundamentals, 11 (1972) 509-517.
}

double HSubstance::GET_LIQUID_DENSITY(const SUBSTANCE_TYPE type, const double temperature) const {
	double density;
	//see https://gist.github.com/n7275/8676c064fef5f48680b5ba815f24e2bf
	switch (type) {
	case SUBSTANCE_TYPE::O2:
		if (temperature < CRITICAL_T[(int)SUBSTANCE_TYPE::O2]) {
			density = 1434.338998096669 + 30827.66466562366 / (temperature - 186.3966881148979);
		}
		else {
			density = 44.24461555143480 + 7784.502442355128 / (temperature - 136.05498694800465);
		}
		break;
	case SUBSTANCE_TYPE::H2:
		if (temperature < CRITICAL_T[(int)SUBSTANCE_TYPE::H2]) {
			density = 136.4894046680936 + 3242.617524782929 / (temperature - 67.46034096292647);
		}
		else {
			density = 0.741833633973125 + 642.4040759445162 / (temperature - 17.5701803944558);
		}
		break;
	case SUBSTANCE_TYPE::N2:
		if (temperature < CRITICAL_T[(int)SUBSTANCE_TYPE::N2]) {
			density = 734.3287921946625 + 9878.83146453045 / (temperature - 146.65628914669438);
		}
		else {
			density = 17.85307222754917 + 4418.262547908501 / (temperature - 107.28230096889227);
		}
		break;
	default:
		density = L_DENSITY[(int)type];
	}
	return density;
}

double HSubstance::Condense(double deltaT)
{
	return 0.0;
}

double HSubstance::Boil(double deltaT)
{
	return 0.0;
}

double HSubstance::BoilAll()
{
	return 0.0;
}

void HSubstance::SetTemp(double _temp)
{
}

HSubstance HSubstance::operator*(float mult) {
	return HSubstance(type, mass * mult, Q * mult, vapor_mass * mult);
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
