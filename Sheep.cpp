#include "stdafx.h"
#include "Sheep.h"
#include "World.h"

Sheep::Sheep(int x, int y, World& world) : Animal(x, y, world)
{
	strength = 4;
	initiative = 4;
	icon = 'm';
}

Sheep::Sheep(int x, int y, World& world, int strength) : Animal(x, y, world, strength) {

	initiative = 4;
	icon = 'm';
}


Sheep::~Sheep()
{
}


Organism* Sheep::clone(int x, int y) {
	return new Sheep(x, y, *world);
}