#include <iostream>
#include <sstream>

#include "Simulation.h"

int main() {
	int holeCount = 2;
	int playerCount = 1;

	Simulation sim(playerCount, holeCount, 800, 800);

	for (int i = 0; i < playerCount; i++) {
		std::stringstream ss;
		ss << "Player " << i + 1;
		sim.addRandomPlayer(ss.str());
	}

	sim.simulate();

	return 0;
}