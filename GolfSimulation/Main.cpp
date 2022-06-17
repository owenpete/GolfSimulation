#include <iostream>
#include <sstream>

#include "Simulation.h"

int main() {
	int holeCount = 18;
	int playerCount = 8;

	Simulation sim(holeCount);

	sim.addCustomPlayer("John", 0, 0, 0);
	sim.addCustomPlayer("Jill", 100, 100, 100);
	/*
	for (int i = 0; i < playerCount; i++) {
		std::stringstream ss;
		ss << "Player " << i + 1;
		sim.addRandomPlayer(ss.str());
	}
	*/
	sim.simulate();
	sim.displayLeaderboard('c');

	return 0;
}