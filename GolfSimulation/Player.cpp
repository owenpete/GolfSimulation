#include <iostream>
#include <vector>

#include "Player.h"

std::string name;
int power;
int accuracy;
int control;
int strokes;
std::vector<int> scoreCard;

Player::Player(std::string playerName, int playerPower, int playerAccuracy, int playerControl) : 
	name(playerName),
	power(playerPower),
	accuracy(playerAccuracy),
	control(playerControl),
	strokes(0)
{
}

const void Player::addStroke() {
	strokes++;
}

const void Player::addScore(int score) {
	scoreCard.push_back(score);
}
