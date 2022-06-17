#include <iostream>
#include <sstream>

#include "Simulation.h"

int main() {
	int holeCount = 18;
	int playerCount = 100;

	Simulation sim(holeCount);

	for (int i = 0; i < playerCount; i++) {
		std::stringstream ss;
		ss << "Player " << i + 1;
		sim.addRandomPlayer(ss.str());
	}

	sim.simulate();
	sim.displayLeaderboard();

	return 0;
}