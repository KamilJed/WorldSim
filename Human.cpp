#include "stdafx.h"
#include "Human.h"
#include "World.h"
#include "curses.h"
#include <string>
#include <iostream>

Human::Human(int x, int y, World& world) : Animal(x, y, world)
{
	initiative = 4;
	strength = 5;
	icon = 'Y';
	turnsRemaining = 0;
	world.setHuman(this);
}

Human::Human(int x, int y, World& world, int turns, bool spec, int strength) : Animal(x, y, world, strength) {

	initiative = 4;
	strength = 5;
	icon = 'Y';
	turnsRemaining = turns;
	special = spec;
	world.setHuman(this);
}


Human::~Human()
{
	world->delHuman();
}

void Human::draw() {

	if (has_colors() == TRUE)
	{
		if (special) {
			init_pair(4, COLOR_YELLOW, COLOR_BLUE);
			attron(COLOR_PAIR(4));
			mvprintw(posY + 1, posX + 1, &icon);
			attroff(COLOR_PAIR(4));
		}
		else if (turnsRemaining < 0) {
			init_pair(5, COLOR_YELLOW, COLOR_RED);
			attron(COLOR_PAIR(5));
			mvprintw(posY + 1, posX + 1, &icon);
			attroff(COLOR_PAIR(5));
		}
		else {
			init_pair(2, COLOR_YELLOW, COLOR_BLACK);
			attron(COLOR_PAIR(2));
			mvprintw(posY + 1, posX + 1, &icon);
			attroff(COLOR_PAIR(2));
		}
		
	}
	else mvprintw(posY + 1, posX + 1, &icon);
}

bool Human::action() {

	clear();
	mvprintw(0, 0, "Kamil Jedrzejczak 171660");
	world->drawWorld();

	int dX = 0, dY = 0;
	do {
		dX = dY = 0;
		do {
			world->setZn(getch());
		} while (world->getZn() != KEY_UP && world->getZn() != KEY_DOWN && world->getZn() != KEY_LEFT && world->getZn() != KEY_RIGHT &&
			world->getZn() != 's' && world->getZn() != 'S' && world->getZn() != 'l' && world->getZn() != 'L' && world->getZn() != ESC &&
			world->getZn() != 'e' && world->getZn() != 'E');
		

		switch (world->getZn()) {

		case KEY_UP:
			dY = -1;
			break;
		case KEY_DOWN:
			dY = 1;
			break;
		case KEY_RIGHT:
			dX = 1;
			break;
		case KEY_LEFT:
			dX = -1;
			break;
		case 'e':
		case 'E':
			if (turnsRemaining == 0) {
				special = true;
				turnsRemaining = 5;
			}
			break;
		}
	} while (posY + dY < 0 || posY + dY >= world->getSizeY() || posX + dX < 0 || posX + dX >= world->getSizeX());
	
	Organism *field = world->isEmpty(posX + dX, posY + dY);

	posX += dX;
	posY += dY;

	world->unset(posX - dX, posY - dY);

	if ((dX != 0 || dY != 0) && field != nullptr) return collision(field, dX, dY);
	else {
		world->set(this);
		return false;
	}
}

Organism* Human::clone(int x, int y) {
	return new Human(x, y, *world);
}

bool Human::getSpecial() {
	return special;
}

int Human::getTurns() {
	return turnsRemaining;
}

std::string Human::getFlatOrganism() {

	std::string organismFlat;

	organismFlat += icon;
	organismFlat += ' ';
	organismFlat += std::to_string(initiative);
	organismFlat += ' ';
	organismFlat += std::to_string(strength);
	organismFlat += ' ';
	organismFlat += std::to_string(posX);
	organismFlat += ' ';
	organismFlat += std::to_string(posY);
	organismFlat += ' ';
	organismFlat += std::to_string(special);
	organismFlat += ' ';
	organismFlat += std::to_string(turnsRemaining);

	return organismFlat;
}

bool Human::escape(Organism* organism, int dX, int dY) {

	if (special && organism->getStrength() >= strength) {

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

bool Human::collision(Organism* organism, int dX, int dY) {

	if (special && organism->getStrength() > strength && escape(organism, dX, dY)) return false;
	else return Animal::collision(organism, dX, dY);
}

void Human::abilityControl() {

	if (turnsRemaining < 0)turnsRemaining++;
	else if(turnsRemaining != 0)turnsRemaining--;
	
	if (turnsRemaining == 0 && special == true) {
		turnsRemaining = -5;
		special = false;
	}
}