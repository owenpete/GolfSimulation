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
	strokes(1)
{
}

const void Player::addStroke() {
	strokes++;
}
