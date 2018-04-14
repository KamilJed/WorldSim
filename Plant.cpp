#include "stdafx.h"
#include "Plant.h"
#include "World.h"
#include "Grass.h"
#include "curses.h"

Plant::Plant(int x, int y, World& world) : Organism(x, y, world){
	initiative = 0;
	icon = 'p';
}


Plant::~Plant(){
}

void Plant::draw() {

	if (has_colors() == TRUE)
	{
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(3));
		mvprintw(posY + 1, posX + 1, &icon);
		attroff(COLOR_PAIR(3));
	}
	else mvprintw(posY + 1, posX + 1, &icon);
}

bool Plant::action() {

	if (rand() % 100 < 20) {

		int maxX = world->getSizeX();
		int maxY = world->getSizeY();

		for (int i = -1; i < 2; i++) {

			for (int j = -1; j < 2; j++) {

				if (posY + i < 0 || posY + i >= maxY || (i == 0 && j == 0))break;
				if (posX + j >= 0 && posX + j < maxX && world->isEmpty(posX + j, posY + i) == nullptr) {

					world->addBaby(clone(posX + j, posY + i));
					return false;
				}
			}
		}
	}

	return false;
}

int Plant::boost() {
	return 0;
}

bool Plant::isPoisonous() {
	return false;
}