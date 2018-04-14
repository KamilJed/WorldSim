#include "stdafx.h"
#include "Dandelion.h"
#include "World.h"

Dandelion::Dandelion(int x, int y, World& world) : Plant(x, y, world)
{
	strength = 0;
	icon = 'd';
}


Dandelion::~Dandelion()
{
}

bool Dandelion::action() {

	for (int i = 0; i < 3; i++) {
		Plant::action();
	}
	return false;
}

Organism* Dandelion::clone(int x, int y) {
	return new Dandelion(x, y, *world);
}