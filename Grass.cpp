#include "stdafx.h"
#include "Grass.h"
#include "World.h"

Grass::Grass(int x, int y, World& world) : Plant(x, y, world)
{
	strength = 0;
	icon = 'g';
}


Grass::~Grass()
{
}

Organism* Grass::clone(int x, int y) {
	return new Grass(x, y, *world);
}