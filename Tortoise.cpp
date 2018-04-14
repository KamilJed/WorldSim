#include "stdafx.h"
#include "Tortoise.h"


Tortoise::Tortoise(int x, int y, World& world) : Animal(x, y, world)
{
	strength = 2;
	initiative = 1;
	icon = 'O';
}

Tortoise::Tortoise(int x, int y, World& world, int strength) : Animal(x, y, world, strength) {

	initiative = 1;
	icon = 'O';
}


Tortoise::~Tortoise()
{
}

bool Tortoise::action() {

	if (rand() % 100 < 25) {
		return Animal::action();
	}
	else return false;
}

bool Tortoise::collision(Organism* organism, int dX, int dY) {
	
	if (icon == organism->getIcon())return Animal::collision(organism, dX, dY);
	else return Animal::collision(organism, dX, dY);
}

Organism* Tortoise::clone(int x, int y) {
	return new Tortoise(x, y, *world);
}

bool Tortoise::deflectAttack(Organism* organism) {
	if (organism->getStrength() < 5)return true;
	else return false;
}