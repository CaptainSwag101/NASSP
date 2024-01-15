#pragma once

enum ThermalPolar {
	directional,
	cardioid,
	subcardioid,
	omni
};

class TObject {
public:
	bool external;
	double energy;
	double c;
	double isolation;
	double area;
	double posX, posY, posZ;
	double mass;
	double temperature;
	ThermalPolar polar;
};