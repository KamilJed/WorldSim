#include "stdafx.h"
#include "DeadlyNightshade.h"


DeadlyNightshade::DeadlyNightshade(int x, int y, World& world) : Plant(x, y, world)
{
	strength = 99;
	icon = 'N';
}


DeadlyNightshade::~DeadlyNightshade()
{
}

bool DeadlyNightshade::isPoisonous() {
	return true;
}

Organism* DeadlyNightshade::clone(int x, int y) {
	return new DeadlyNightshade(x, y, *world);
}