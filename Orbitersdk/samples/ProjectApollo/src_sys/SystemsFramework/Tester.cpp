#include <iostream>
#include "SystemsFramework.h"

int main() {
	SystemsFramework saturn_systems = SystemsFramework("SaturnSystems.cfg");
	SystemsFramework lm_systems = SystemsFramework("LEMSystems.cfg");

	std::cout << "Saturn Systems:" << std::endl;
	for (auto& pair : saturn_systems.Hydraulic) {
		std::cout << std::get<0>(pair) << std::endl;
	}


	std::cout << std::endl << "LM Systems:" << std::endl;
	for (auto& pair : lm_systems.Hydraulic) {
		std::cout << std::get<0>(pair) << std::endl;
	}

	return 0;
}