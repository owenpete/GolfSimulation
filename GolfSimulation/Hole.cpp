#include "Hole.h"

int distance;
int greenSize;
float holeSize;
int par;

Hole::Hole(int dist, int greenSz) :
	distance(dist),
	greenSize(greenSz),
	holeSize(0.125)
{
	if (distance <= 250) {
		par = 3;
	}
	else if (distance <= 470) {
		par = 4;
	}
	else if (distance <= 690) {
		par = 5;
	}
	else {
		par = 6;
	}
}
