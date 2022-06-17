#pragma once
#include "Player.h"
#include "Hole.h"
#include "Club.h"
#include <iostream>
#include <vector>
#include <map>

class Simulation
{
	private:
		int holeCount;
		int minGreenSize;
		int maxGreenSize;
		std::vector<Hole> holes;
		int playerCount;
		std::vector<Player> players;
		std::vector<Club> clubs;
		std::vector<std::string> clubOrder;
	public:
		Simulation(int playerCt, int holeCt, int minHoleLen = 100, int maxHoleLen = 600);
		const void addRandomPlayer(std::string name);
		const void addCustomPlayer(std::string name, int power, int accuracy, int control);
		const std::vector<Player> getPlayerList();
		const float generateRandomNumber(float max, float min = 0);
		const float calculatePlayerPowerMultiplier(int pwr);
		const float calculatePlayerAccuracy(int acc);
		const float calculatePlayerControl(int ctrl);
		const float calculateShotAngle(float maxAngle);
		const float calculateShotDistance(float plusMinusPercent, float clubRange, float disFromHole, float shotAngle);
		const int playHole(int holeNumber, int playerNumber);
		const void simulate();
		const void displayLeaderboard(char mode = 'n');
};

