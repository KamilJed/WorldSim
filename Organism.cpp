#include "stdafx.h"
#include "Organism.h"
#include "World.h"
#include "Plant.h"
#include "Animal.h"
#include "curses.h"
#include <string>
#include <iostream>

Organism::Organism() {
}

Organism::Organism(int x, int y, World& world){

	this->posX = x;
	this->posY = y;
	this->icon = 'o';
	this->initiative = 0;
	this->strength = 0;
	this->world = &world;
}

Organism::Organism(int x, int y, World& world, int strength) {

	this->posX = x;
	this->posY = y;
	this->icon = 'o';
	this->initiative = 0;
	this->strength = strength;
	this->world = &world;
}


Organism::~Organism(){
}

int Organism::getX() {
	return posX;
}

int Organism::getY() {
	return posY;
}

int Organism::getStrength() {
	return strength;
}

int Organism::getInitiative() {
	return initiative;
}

void Organism::draw() {
	mvprintw(posY + 1, posX + 1, &icon);
}

bool Organism::collision(Organism* organism, int dX, int dY) {

	world->unset(posX - dX, posY - dY);

	std::string eventInfo;

	if (Plant* p = dynamic_cast<Plant*>(organism)) {

		strength += p->boost();
		if (p->isPoisonous()) {

			eventInfo = icon;
			eventInfo += " has been poisoned";
			world->setInfo(eventInfo.c_str());
			world->erase(organism);
			world->erase(this);
			return true;
		}
	}
	if (Animal* a = dynamic_cast<Animal*>(organism)) {

		if (a->escape(dX, dY)) {

			eventInfo = organism->getIcon();
			eventInfo += " has escaped";
			world->setInfo(eventInfo.c_str());
			world->set(this);
			return false;
		}
	}
	if (organism->deflectAttack(this)) {

		eventInfo = organism->getIcon();
		eventInfo += " has deflected the attack";
		world->setInfo(eventInfo.c_str());
		posX -= dX;
		posY -= dY;
		world->set(this);
		return false;
	}
	else if (this->strength < organism->getStrength()) {

		eventInfo = organism->getIcon();
		eventInfo += " killed ";
		eventInfo += icon;
		world->setInfo(eventInfo.c_str());

		World* w = this->world;

		world->erase(this);
		w->set(organism);
		return true;
	}
	else {
		eventInfo = icon;
		eventInfo += " killed ";
		eventInfo += organism->getIcon();
		world->setInfo(eventInfo.c_str());

		world->erase(organism);
		world->set(this);
		return false;
	}
}

char Organism::getIcon() {
	return icon;
}

bool Organism::deflectAttack(Organism* organism) {
	return false;
}

std::string Organism::getFlatOrganism() {

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

	return organismFlat;
}