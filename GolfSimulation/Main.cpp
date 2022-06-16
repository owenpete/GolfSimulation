#include <iostream>
#include <sstream>

#include "Simulation.h"

int main() {
	int holeCount = 18;
	int playerCount = 8;

	Simulation sim(playerCount, holeCount, 300, 300);

	for (int i = 0; i < playerCount; i++) {
		std::stringstream ss;
		ss << "Player " << i + 1;
		sim.addRandomPlayer(ss.str());
	}

	sim.simulate();

	return 0;
}