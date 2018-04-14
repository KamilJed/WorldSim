#include "stdafx.h"
#include "Fox.h"
#include "World.h"


Fox::Fox(int x, int y, World& world) : Animal(x, y, world)
{
	strength = 3;
	initiative = 7;
	icon = 'f';
}

Fox::Fox(int x, int y, World& world, int strength) : Animal(x, y, world, strength) {

	initiative = 7;
	icon = 'f';
}


Fox::~Fox()
{
}

bool Fox::action() {

	int maxX = world->getSizeX();
	int maxY = world->getSizeY();
	int i = rand() % 3 - 1;

	for (int a = 0; a < 3; a++) {

		int j = rand() % 3 - 1;

		for (int b = 0; b < 2; b++) {

			if (posY + i < 0 || posY + i >= maxY || (i == 0 && j == 0)) {
				
				if (++j == 2)j = -1;
				break;
			}
			if (posX + j >= 0 && posX + j < maxX) {

				Organism* organism = world->isEmpty(posX + j, posY + i);

				if (organism == nullptr) {
					world->unset(posX, posY);
					posX += j;
					posY += i;
					world->set(this);
					return false;
				}
				else if (organism->getStrength() <= strength || organism->getIcon() == icon) {
					
					posX += j;
					posY += i;
					return Animal::collision(organism, j, i);
				}
			}
		}
		
		if (++i == 2)i = -1;
	}

	return false;
}

Organism* Fox::clone(int x, int y) {
	return new Fox(x, y, *world);
}