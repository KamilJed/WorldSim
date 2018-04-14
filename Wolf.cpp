#include "stdafx.h"
#include "Wolf.h"
#include "World.h"


Wolf::Wolf(int x, int y, World& world) : Animal(x, y, world)
{
	strength = 9;
	initiative = 5;
	icon = 'V';
}

Wolf::Wolf(int x, int y, World& world, int strength) : Animal(x, y, world, strength) {

	initiative = 5;
	icon = 'V';
}


Wolf::~Wolf()
{
}


Organism* Wolf::clone(int x, int y) {
	return new Wolf(x, y, *world);
}