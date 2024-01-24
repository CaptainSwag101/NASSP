#include "SystemsFramework.h"

#include <chrono>
#include <iostream>

int main() {
	auto started_at = std::chrono::steady_clock::now();

	SystemsFramework saturn_systems = SystemsFramework("SaturnSystems.cfg");
	SystemsFramework lm_systems = SystemsFramework("LEMSystems.cfg");

	auto ended_at = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(ended_at - started_at);
	std::cout << "Batched ticks took " << (elapsed.count() / 1000000.0) << " milliseconds." << std::endl;

	std::cout << "Saturn Systems:" << "\n";
	for (auto& pair : saturn_systems.Hydraulic) {
		std::cout << std::get<0>(pair) << "\n";
	}
	
	std::cout << std::endl << "LM Systems:" << "\n";
	for (auto& pair : lm_systems.Hydraulic) {
		std::cout << std::get<0>(pair) << "\n";
	}
	

	return 0;
}