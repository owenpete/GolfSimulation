#include <iostream>

#include "Club.h"

std::string clubName;
int clubRange;

Club::Club(){ }

Club::Club(std::string name, int dist) :
	clubName(name),
	clubRange(dist)
{
}
