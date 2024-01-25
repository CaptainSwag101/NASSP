#pragma once

#include <map>
#include <memory>
#include <string>
#include "OrbiterAPI.h"

class ShipObject {
public:
	int max_stage;

	virtual void Refresh(double dt);
	virtual void Load(FILEHANDLE scn);
	virtual void Save(FILEHANDLE scn);
	//virtual std::shared_ptr<TObject> GetThermalInterface();
	virtual void UpdateFlow(double dt);
};

class ShipSystem {
public:
	std::map<const std::string, std::shared_ptr<ShipObject>> ObjectMap;
};