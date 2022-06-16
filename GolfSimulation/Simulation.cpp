#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

#include "Simulation.h"
#include "Player.h"
#include "Hole.h"
#include "Club.h"

int holeCount;
// green size 20 - 27 yards
int minGreenSize;
int maxGreenSize;
std::vector<Hole> holes; // in yards
int playerCount;
std::vector<Player> players;
std::vector<Club> clubs;
std::map<std::string, int>::iterator clubsIter;

Simulation::Simulation(int playerCt, int holeCt, int minHoleLen, int maxHoleLen) :
	playerCount(playerCt),
	holeCount(holeCt),
	clubs({
		 Club("driver", 320),
		 Club("3Wood", 300),
		 Club("5Wood", 290),
		 Club("4Iron", 255),
		 Club("5Irol",  240),
		 Club("6Iron", 230),
		 Club("7Iron", 215),
		 Club("8Iron", 200),
		 Club("9Iron", 185),
		 Club("pitchingWedge", 170),
		 Club("gapWedge", 135),
		 Club("sandWedge", 120),
		 Club("lobWedge", 95),
		// can only use putter on green
		 Club("putter", maxGreenSize)
	}),
	minGreenSize(20),
	maxGreenSize(27)
{
	// seed random numbers
	srand (static_cast <unsigned> (time(0)));

	for (int i = 0; i < holeCount; i++) {
		holes.push_back(Hole(generateRandomNumber(maxHoleLen, minHoleLen), generateRandomNumber(maxGreenSize, minGreenSize)));
	}
}

const void Simulation::addRandomPlayer(std::string name) {
	const float power = generateRandomNumber(100, 0);
	const float accuracy = generateRandomNumber(100, 0);
	const float control = generateRandomNumber(100, 0);
	players.push_back(Player(name, power, accuracy, control));
}

const void Simulation::addCustomPlayer(std::string name, int power, int accuracy, int control) {
	players.push_back(Player(name, power, accuracy, control));
}

const std::vector<Player> Simulation::getPlayerList() {
	return players;
}

const float Simulation::generateRandomNumber(float max, float min) {
	const float number = min + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(max-min)));

	return number;
}

const float Simulation::calculatePlayerPower(int pwr) {
	/*
		100 : 1.20
		 50 : 1.00
		  0 : 0.80

		  highest 1.6
		  lowest 0.8
	*/

	const float powerCoefficient = (pwr * 0.004) + 0.8f;

	return powerCoefficient;
}

const float Simulation::calculatePlayerAccuracy(int acc) {
	/*
		in angles

		100 : 10
		 50 : 30
		  0 : 50 
	*/

	const float accuracyCoefficient = 50 - (acc * 0.4f);
	
	return accuracyCoefficient;
}

const float Simulation::calculatePlayerControl(int ctrl) {
	/*
		100 : 0.0050 50
		 50 : 0.0125 125
		  0 : 0.0200 200
	*/

	const float controlCoefficient = 0.02f - (ctrl * 0.00015f);

	return controlCoefficient;
}

const float Simulation::calculateShotAngle(float maxAngle) {
	const float angle = generateRandomNumber(maxAngle, -maxAngle);
	return angle;
}

const float Simulation::calculateShotDistance(float plusMinusPercent, float clubRange, float disFromHole) {
	const float percentage = generateRandomNumber(plusMinusPercent, -plusMinusPercent);

	std::cout << "Shot Distance offset Percentage: " << 1- percentage << std::endl << std::endl << std::endl;

	return ((clubRange < disFromHole) ? clubRange : disFromHole) * (1 - percentage);
}

const int Simulation::playHole(int holeNumber, int playerNumber) {
	const Player player = players[playerNumber];
	const Hole hole = holes[holeNumber];
	float currentDisFromHole = hole.distance;
	Club currentClub;

	while (currentDisFromHole != 0) {
		const float playerPower = calculatePlayerPower(player.power);
		const float playerAccuracy = calculatePlayerAccuracy(player.accuracy);
		const float playerControl= calculatePlayerControl(player.control);
		for (int i = 0; i < clubs.size(); i++) {
			if (clubs[i].clubRange * playerPower < currentDisFromHole) {
				currentClub = (i == 0) ? clubs[i] : clubs[i - 1];
				break;
			}
			else if (i == clubs.size() - 1) {
				currentClub = clubs[clubs.size() - 1];
			}
		}
		const float adjustedClubRange = playerPower * currentClub.clubRange;
		const float shotAngle = calculateShotAngle(playerAccuracy);
		const float shotDistance= calculateShotDistance(playerControl, adjustedClubRange, currentDisFromHole);

		std::cout << "Club Name: " << currentClub.clubName<< std::endl;
		std::cout << "Club Range RAW: " << currentClub.clubRange << std::endl;
		std::cout << "Club Range (calc): " << adjustedClubRange << std::endl;
		std::cout << "Distance from hole: " << currentDisFromHole << std::endl << std::endl;

		std::cout << "Power Rating RAW: " << player.power << std::endl;
		std::cout << "Accuracy Rating RAW: " << player.accuracy << std::endl;
		std::cout << "Control Rating RAW: " << player.control << std::endl << std::endl;

		std::cout << "Shot Power (calc): " << playerPower << std::endl;
		std::cout << "Shot Accuracy (calc): " << playerAccuracy << std::endl;
		std::cout << "Shot Control (calc): " << playerControl << std::endl;
		std::cout << "Shot Angle (calc): " << shotAngle << std::endl;
		std::cout << "Shot Distance (calc): " << shotDistance << std::endl << std::endl;

		std::cout << std::endl;

		currentDisFromHole -= shotDistance;

		std::cout << "Distance from Hole after shot: " << currentDisFromHole << std::endl;
		std::cout << "------------------------------------------------------------------" << std::endl << std::endl;

		break;
	}

	return 0;
}

const void Simulation::simulate() {
	for (int h = 0; h < 1; h++) {
		for (int p = 0; p < playerCount; p++) {
			playHole(h, p);
		}
	}
}
