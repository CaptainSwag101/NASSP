#pragma once

#include "Generic.h"
#include "Thermal.h"

#include <array>
#include <map>
#include <string>
#include <vector>

#include "OrbiterAPI.h"

enum SUBSTANCE_TYPE {
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
constexpr size_t MAX_SUB = 9;

constexpr double R_CONST = 8314.4621;	//(L*Pa)/(mol*K)
//										O2					H2					H20					N2					CO2					GLYCOL					Aerozine-50				N2O4					He
const double MMASS			[MAX_SUB] = { 31.998,			2.01588,			18.01528,			28.0134,			44.01,				33.434432,				92.146,					92.01,					4.00260 };//g/mol
const double SPECIFICC_GAS	[MAX_SUB] = { 0.658,			10.183,				1.4108,				0.743,				0.6553,				3.625769,				0.48102,				4.6,					3.12 };//J/g-K .. assume constant
const double SPECIFICC_LIQ	[MAX_SUB] = { 1.1519,			9.668,				4.184,				1.7848,				0.858,				3.691041,				1.0724,					1.5525,					5.193 };//J/g-K .. assume constant
const double L_DENSITY		[MAX_SUB] = { 1141.0,			70.0,				1000.0,				807.0,				1014.0,				1038.5,					899.0,					1450.0,					0.164 };//g/L @ 103kPa ..assume constant wrt. temp
const double BULK_MOD		[MAX_SUB] = { 1.172e+9,			50.13e6,			2.18e6,				1.02E9,				32e6,				2.55e6,					1.47397e6,				1.362e6,				10e6 };//Pa .. assume constant and converted from m^3 to L
const double CRITICAL_P		[MAX_SUB] = { 4926063.722233855,1303085.962148109,	19910602.43884709,	3300253.307024634,	7800213.020695794,	3097566.149152389,		14500299.44342058,		9998268.775903003,		228416.3259285132 };//Pa.. critical pressure
const double CRITICAL_T		[MAX_SUB] = { 154.7,			33.2,				647.3,				126.2,				304.4,				256.9525,				607.15,					431.15,					5.19 };//K.. critical temperature
const double ANTIONE_A		[MAX_SUB] = { 9.3199656,		6.59723,			12.490095,			9.0020008,			12.0892,			8.32957,				13.7222,				14.47645,				4.41952 };//Antione Equation A constant gives results in bar, must be converter to Pa	[1]
const double ANTIONE_B		[MAX_SUB] = { 838.91339,		133.793,			4658.1375,			694.78356,			2353.762,			3158.1575,				5309.7973,				4256.07694,				18.65037 };//Antione Equation B constant gives results in bar, must be converter to Pa	[2]
const double ACENTRIC		[MAX_SUB] = { 0.022,			-0.216,				0.345,				0.040,				0.288,				0.416,					0.316,					0.0141345,				-0.390 };//[3] Acentric factor
const double VDW_B			[MAX_SUB] = { 9.957E-4,			0.015805,			0,					0.0387,				0,					0,						0,						0,						0, };// Van der Waals equation 'b' coefficient in l/g
//source for [1-3] are https://onlinelibrary.wiley.com/doi/pdf/10.1002/9781118135341.app1 or where they differ from the source they were adjusted by M. Hume to better fit a wide range of temperatures.
// [3] https://nvlpubs.nist.gov/nistpubs/Legacy/IR/nbsir86-3054.pdf

const double FaradaysConstant = 96485.3321233100184; //Coulombs/mol

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
	void operator+=(HSubstance add);	// Add some more substance
	void operator-=(HSubstance sub);	// Remove some amount of substance
	HSubstance operator*(float mult);	// Return a substance block that is multiplied in all aspects by the given amount
	double VAPENTH() const;
	double GET_LIQUID_DENSITY(const SUBSTANCE_TYPE type, const double temperature) const;
	double Condense(double deltaT);
	double Boil(double deltaT);
	double BoilAll();
	void SetTemp(double _temp);
};

class HVolume {
public:
	std::array<HSubstance, MAX_SUB> composition;

	void operator+=(HVolume add);	// Add two volumes together
	void operator+=(HSubstance add);	// Add some substance to the volume
	HVolume Break(const double vol, const std::vector<SUBSTANCE_TYPE> substance_mask, const double maxMass = 0.0);	  // Break out 'vol' liters from this volume into a new one
	double GetMass();	// Total mass inside the volume
	double GetQ();
	double Q;
	double press;					//total press... sum of all p_press (Pa)
	double temperature;				//averaged temp of volume... (K)
	double volume;					//liters
	void ThermalComps(double dt);	//levels temp throughout all subst...much like stirring a tank,only instanaeously
	void Void();					//empty all inside the volume
};

class HObject : public ShipObject {
public:
	HObject();
	virtual void Refresh(double deltaT);
	virtual void Save(FILEHANDLE scn);
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
	void Close();
	void Open();
	double GetPress();
	double GetTemp();
	void thermic(double _en);
	int Flow(HVolume block);
	HVolume GetFlow(double dPdT, double maxMass = 0.0);
	virtual void refresh(double dt);
	virtual void Save(FILEHANDLE scn);
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