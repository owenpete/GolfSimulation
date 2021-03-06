#include <iostream>
#include <vector>

#include "Player.h"

std::string name;
int power;
int accuracy;
int control;
int strokes;
int totalStrokes;
std::vector<int> scoreCard;
int totalScore;

Player::Player(std::string playerName, int playerPower, int playerAccuracy, int playerControl) : 
	name(playerName),
	power(playerPower),
	accuracy(playerAccuracy),
	control(playerControl),
	strokes(0),
	totalStrokes(0),
	totalScore(0)
{
}

const void Player::addStroke() {
	strokes++;
	totalStrokes++;
}

const void Player::addTotalScore(int strokes, int par) {
	totalScore += strokes - par;
}

const void Player::resetStrokes() {
	strokes = 0;
}

const void Player::addScore(int score) {
	scoreCard.push_back(score);
}
