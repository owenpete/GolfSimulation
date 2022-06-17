#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <string>

#include "Simulation.h"
#include "Player.h"
#include "Hole.h"
#include "Club.h"

// green size 20 - 27 yards
int minGreenSize;
int maxGreenSize;
std::vector<Hole> holes; // in yards
std::vector<Player> players;
std::vector<Club> clubs;
std::map<std::string, int>::iterator clubsIter;

Simulation::Simulation(int holeCount, int minHoleLen, int maxHoleLen) :
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

const float Simulation::calculatePlayerPowerMultiplier(int pwr) {
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

		100 : 5 
		 50 : 10 
		  0 : 15 
	*/

	const float accuracyCoefficient = 15 - (acc * 0.1f);
	
	return accuracyCoefficient;
}

const float Simulation::calculatePlayerControl(int ctrl) {
	/*
		100 : 0.0050
		 50 : 0.0125
		  0 : 0.0200
	*/

	const float controlCoefficient = 0.02f - (ctrl * 0.00015f);

	return controlCoefficient;
}

const float Simulation::calculateShotAngle(float maxAngle) {
	const float angle = generateRandomNumber(maxAngle, -maxAngle);
	return angle;
}

const float Simulation::calculateShotDistance(float plusMinusPercent, float clubRange, float disFromHole, float shotAngle) {
	const float percentage = generateRandomNumber(plusMinusPercent, -plusMinusPercent);
	const float distance = std::cos(2 * (2 * acos(0.0)) * (shotAngle / 360)) * ((clubRange < disFromHole) ? clubRange : disFromHole) * (1 - percentage);
	const float d = ((clubRange < disFromHole) ? clubRange : disFromHole)* (1 - percentage);

	/*
	std::cout << "\nshot angle " << shotAngle << std::endl;
	std::cout << "Shot Distance (no COS): " << d << std::endl;
	std::cout << "Shot Distance offset Percentage: " << 1 - percentage << std::endl << std::endl << std::endl;
	*/
	return distance;
}


const int Simulation::playHole(int holeNumber, int playerNumber) {
	Player &player = players[playerNumber];
	Hole &hole = holes[holeNumber];
	float currentDisFromHole = hole.distance;
	Club currentClub;

	while (currentDisFromHole != 0) {
		const float playerPowerMultiplier = calculatePlayerPowerMultiplier(player.power);
		const float playerAccuracy = calculatePlayerAccuracy(player.accuracy);
		const float playerControl= calculatePlayerControl(player.control);

		for (int i = 0; i < clubs.size(); i++) {
			bool isLastClub = i == clubs.size() - 1;
			bool isDisLargerThanRange =  currentDisFromHole > clubs[i].clubRange * playerPowerMultiplier;
			if (isLastClub) {
				currentClub = (currentDisFromHole <= hole.greenSize) ?
					clubs[i]
					:
					clubs[i - 1];
			}
			else if (isDisLargerThanRange) {
				if (i == 0) {
					if (player.strokes == 0) {
						currentClub = clubs[i];
					}
					else {
						continue;
					}
					break;
				}
				else if (player.strokes == 0) {
					if (i == 1) {
						currentClub = clubs[i];
					}
					else {
						currentClub = clubs[i - 1];
					}
					break;
				}
				else {
					if (i == 1) {
						currentClub = clubs[i];
					}
					else {
						currentClub = clubs[i - 1];
					}
					break;
				}
			}
		}
		const float adjustedClubRange = playerPowerMultiplier * currentClub.clubRange;
		const float shotAngle = calculateShotAngle(playerAccuracy);
		const float shotDistance= calculateShotDistance(playerControl, adjustedClubRange, currentDisFromHole, shotAngle);

		/*
		std::cout << player.name << std::endl;
		std::cout << "Power Rating RAW: " << player.power << std::endl;
		std::cout << "Accuracy Rating RAW: " << player.accuracy << std::endl;
		std::cout << "Control Rating RAW: " << player.control << std::endl << std::endl;

		std::cout << "Distance from hole: " << currentDisFromHole << std::endl << std::endl;
		std::cout << "Club Name: " << currentClub.clubName<< std::endl;
		std::cout << "Club Range RAW: " << currentClub.clubRange << std::endl;
		std::cout << "Club Range (calc): " << adjustedClubRange << std::endl;
		std::cout << "Green size: " << hole.greenSize << std::endl << std::endl;

		std::cout << "Shot Power (calc): " << playerPowerMultiplier << std::endl;
		std::cout << "Shot Accuracy (calc): " << playerAccuracy << std::endl;
		std::cout << "Shot Control (calc): " << playerControl << std::endl;
		std::cout << "Shot Angle (calc): " << shotAngle << std::endl;
		std::cout << "Shot Distance (calc): " << shotDistance << std::endl << std::endl;

		std::cout << std::endl;
		*/

		player.addStroke();
		currentDisFromHole -= shotDistance;

		if (currentDisFromHole <= hole.holeSize) {
			player.addScore(player.strokes);
			player.addTotalScore(player.strokes, hole.par);
			player.resetStrokes();
			break;
		}
	}
	return 0;
}

const void Simulation::simulate() {
	for (int h = 0; h < holes.size(); h++) {
		for (int p = 0; p < players.size(); p++) {
			playHole(h, p);
		}
	}
}

const bool compairScores(Player first, Player second) {
	return (first.totalStrokes < second.totalStrokes);
}
const void Simulation::displayLeaderboard() {
	std::vector<Player> playersCopy = players;
	std::sort(playersCopy.begin(), playersCopy.end(), compairScores);
	for (int i = 0; i < playersCopy.size(); i++) {
		Player player = playersCopy[i];

	std::cout <<
		' ' << std::right << std::setfill(' ') << std::setw(4) << i + 1 << ")" << ' ' << std::setfill(' ') << std::setw(15) << player.name << " | " <<
		"\033[31;1m" << std::setfill(' ') << std::setw(3) << player.power << 
		"\033[0m" << ' ' << "\033[32;1m" << std::setfill(' ') << std::setw(3) << player.accuracy << "\033[0m" << ' ' << 
		"\033[34;1m" << std::setfill(' ') << std::setw(3) << player.control << "\033[0m" << ' ' <<
		" | " << "\033[33;1m" << std::setfill(' ') << std::setw(3) << ((player.totalScore > 0) ? ('+' + std::to_string(player.totalScore)) : std::to_string(player.totalScore)) << "\033[0m" <<
		std::endl;
		std::cout << "---------------------------------------" << std::endl;
	}
}
