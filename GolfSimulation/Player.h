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
		std::vector<int> scoreCard;
		Player(std::string name, int power, int accuracy, int control);
		const void addStroke();
};

