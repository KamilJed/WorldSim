#include "stdafx.h"
#include "HeracleumSosnowskyi.h"
#include "World.h"
#include "Animal.h"


HeracleumSosnowskyi::HeracleumSosnowskyi(int x, int y, World& world) : Plant(x, y, world)
{
	strength = 10;
	icon = 'Q';
}


HeracleumSosnowskyi::~HeracleumSosnowskyi()
{
}

bool HeracleumSosnowskyi::isPoisonous() {
	return true;
}

Organism* HeracleumSosnowskyi::clone(int x, int y) {
	return new HeracleumSosnowskyi(x, y, *world);
}

bool HeracleumSosnowskyi::action() {

	int maxX = world->getSizeX();
	int maxY = world->getSizeY();

	for (int i = -1; i < 2; i++) {

		for (int j = -1; j < 2; j++) {

			if (posY + i < 0 || posY + i >= maxY || (i == 0 && j == 0))break;
			if (posX + j >= 0 && posX + j < maxX) {

				Organism* organism = world->isEmpty(posX + j, posY + i);

				if (dynamic_cast<Animal*>(organism)) world->erase(organism);
			}
		}
	}
	return false;
}