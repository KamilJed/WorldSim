#include "stdafx.h"
#include "Antelope.h"
#include "World.h"

Antelope::Antelope(int x, int y, World& world) : Animal(x, y, world)
{
	initiative = 4;
	strength = 4;
	icon = 'A';
}

Antelope::Antelope(int x, int y, World& world, int strength) : Animal(x, y, world, strength) {

	initiative = 4;
	icon = 'A';
}


Antelope::~Antelope()
{
}

Organism* Antelope::clone(int x, int y) {
	return new Antelope(x, y, *world);
}

bool Antelope::action() {

	if (!Animal::action()) return Animal::action();
	else return true;
}

bool Antelope::escape(int dX, int dY) {

	if (rand() % 100 <= 50) {

		int maxX = world->getSizeX();
		int maxY = world->getSizeY();

		for (int i = -1; i < 2; i++) {

			for (int j = -1; j < 2; j++) {

				if (posY + i < 0 || posY + i >= maxY)break;
				if (posX + j >= 0 && posX + j < maxX && world->isEmpty(posX + j, posY + i) == nullptr) {

					world->unset(posX - dX, posY - dY);
					posX += j;
					posY += i;
					world->set(this);
					return true;
				}
			}
		}
	}
	return false;
}

bool Antelope::collision(Organism* organism, int dX, int dY) {

	if (icon != organism->getIcon() && escape(dX, dY)) return false;
	else return Animal::collision(organism, dX, dY);
}