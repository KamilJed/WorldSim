#include "stdafx.h"
#include "Guarana.h"


Guarana::Guarana(int x, int y, World& world) : Plant(x, y, world)
{
	strength = 0;
	icon = 'b';
}


Guarana::~Guarana()
{
}

int Guarana::boost() {
	return 3;
}

Organism* Guarana::clone(int x, int y) {
	return new Guarana(x, y, *world);
}