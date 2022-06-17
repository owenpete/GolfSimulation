#pragma once

#include <iostream>
#include <vector>

class Player
{
	private:
	public:
		std::string name;
		int power;
		int accuracy;
		int control;
		int strokes;
		int totalStrokes;
		std::vector<int> scoreCard;
		int totalScore;
		Player(std::string playerName, int power, int accuracy, int control);
		const void addStroke();
		const void addTotalScore(int strokes, int par);
		const void resetStrokes();
		const void addScore(int score);
};

