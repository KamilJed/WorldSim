#include "stdafx.h"
#include "Animal.h"
#include "World.h"
#include <cstdlib>
#include "curses.h"

Animal::Animal(int x, int y, World& world) : Organism(x, y, world){
	icon = 'a';
	initiative = rand() % 20;
	strength = rand() % 5;
}

Animal::Animal(int x, int y, World& world, int strength) : Organism(x, y, world, strength) {
	icon = 'a';
}


Animal::~Animal(){
}

void Animal::draw() {
	if (has_colors() == TRUE)
	{
		init_pair(1, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		mvprintw(posY + 1, posX + 1, &icon);
		attroff(COLOR_PAIR(1));
	}
	else mvprintw(posY + 1, posX + 1, &icon);
}

bool Animal::action() {

	int dX = 0;
	int dY = 0;

	do {
		dX = rand() % 3 - 1;
	} while (posX + dX < 0 || posX + dX >= world->getSizeX());
	
	do {
		dY = rand() % 3 - 1;
	} while (posY + dY < 0 || posY + dY >= world->getSizeY());

	Organism *field = world->isEmpty(posX + dX, posY + dY);

	posX += dX;
	posY += dY;

	if ((dX != 0 || dY != 0) && field != nullptr) return this->collision(field, dX, dY);
	else {
		world->unset(posX - dX, posY - dY);
		world->set(this);
		return false;
	}
}

bool Animal::collision(Organism* organism, int dX, int dY) {

	std::string eventInfo;

		if (icon == organism->getIcon()) {
			posX -= dX;
			posY -= dY;
			int maxX = world->getSizeX();
			int maxY = world->getSizeY();

			for (int i = -1; i < 2; i++) {

				for (int j = -1; j < 2; j++) {

					if (posY + i < 0 || posY + i >= maxY)break;
					if (posX + j >= 0 && posX + j < maxX && world->isEmpty(posX + j, posY + i) == nullptr) {

						eventInfo = icon;
						eventInfo += " was born!";
						world->setInfo(eventInfo.c_str());
						world->addBaby(clone(posX + j, posY + i));
						return false;
					}
				}
			}
			return false;
		}
		else return Organism::collision(organism, dX, dY);
}

bool Animal::escape(Organism* organism, int dX, int dY) {
	return false;
}