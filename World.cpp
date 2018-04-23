#include "stdafx.h"
#include "curses.h"
#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Human.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Fox.h"
#include "Tortoise.h"
#include "Guarana.h"
#include "DeadlyNightshade.h"
#include "HeracleumSosnowskyi.h"
#include "Antelope.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

World::World(int sizeX, int sizeY){

	this->worldSizeX = sizeX;
	this->worldSizeY = sizeY;
	if (sizeX <= 0 || sizeY <= 0) {
		std::string exception = "Invalid board size!";
		throw exception;
	}
	this->worldMap = new Organism**[sizeY];
	isHuman = false;
	turn = 0;

	for (int i = 0; i < sizeY; i++)worldMap[i] = new Organism*[sizeX]();

	for (int i = 0; i < worldSizeY; i++) {

		for (int j = 0; j < worldSizeX; j++) {

			int character = rand() % 40;

			if (character == 0) addOrganism(new Sheep(j, i, *this));
			
			else if (character == 1) addOrganism(new Wolf(j, i, *this));
			
			else if (character == 2) addOrganism(new Grass(j, i, *this));
			
			if (character == 3 && isHuman == false) {

				addOrganism(new Human(j, i, *this));
				isHuman = true;
				player = dynamic_cast<Human*>(worldMap[i][j]);
			}
			
			else if (character == 4) addOrganism(new Dandelion(j, i, *this));
			
			else if (character == 5) addOrganism(new Fox(j, i, *this));

			else if (character == 6) addOrganism(new Tortoise(j, i, *this));

			else if (character == 7) addOrganism(new Guarana(j, i, *this));

			else if (character == 8) addOrganism(new DeadlyNightshade(j, i, *this));

			else if (character == 9) addOrganism(new HeracleumSosnowskyi(j, i, *this));

			else if (character == 10) addOrganism(new Antelope(j, i, *this));
		}
	}
}


World::~World(){

	delMap();
}

void World::gameInit() {

	raport = "Press any button to start.";
	drawWorld();
	zn = getch();
	while (zn != ESC) {

		newTurn();
		if (!isHuman) zn = getch();
		if (zn == 's' || zn == 'S')	saveWorld();
		else if (zn == 'l' || zn == 'L') loadWorld();
	}
}

void World::drawWorld() {

	clear();

	mvprintw(0, 0, "Kamil Jedrzejczak 171660");

	for (int i = 0; i < worldSizeY; i++) {

		for (int j = 0; j < worldSizeX; j++) {

			if (worldMap[i][j] != nullptr) {

				worldMap[i][j]->draw();
			}
			else mvprintw(i + 1, j + 1, ".");
		}
	}

	info();
}

void World::newTurn() {

	turn++;

	for(std::list<Organism*>::iterator i = initiativeQueue.begin(), end = initiativeQueue.end(); i != end; ){

		if((*i)->action()) i = iter;
		else i++;
	}

	includeBabies();
	if (isHuman)player->abilityControl();
	if(!isHuman)drawWorld();
}

Organism* World::isEmpty(int x, int y) {
	return worldMap[y][x];
}

void World::erase(Organism* organism) {

	iter = std::find(babyList.begin(), babyList.end(), organism);
	if (iter != babyList.end())babyList.erase(iter);

	iter = std::find(initiativeQueue.begin(), initiativeQueue.end(), organism);
	if(iter != initiativeQueue.end())iter = initiativeQueue.erase(iter);

	worldMap[organism->getY()][organism->getX()] = nullptr;

	delete organism;
	organism = nullptr;
}

int World::getSizeX() {
	return worldSizeX;
}

int World::getSizeY() {
	return worldSizeY;
}

void World::set(Organism* organism) {
	worldMap[organism->getY()][organism->getX()] = organism;
}

void World::unset(int x, int y) {
	worldMap[y][x] = nullptr;
}

void World::addToQueue(Organism* organism) {

	if (initiativeQueue.size() == 0) {
		initiativeQueue.push_front(organism);
		return;
	}
	else for (std::list<Organism*>::iterator iter = initiativeQueue.begin(), end = initiativeQueue.end(); iter != end; iter++) {

		if ((*iter)->getInitiative() >= organism->getInitiative())continue;
		else {

			initiativeQueue.insert(iter, organism);
			return;
		}
	}

	initiativeQueue.push_back(organism);
}

void World::info() {

	int rows = getmaxy(stdscr);
	std::string size = "Organisms: ";
	size += std::to_string(initiativeQueue.size());
	attron(A_BOLD);
	if (has_colors() == TRUE)
	{
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(3));
		mvprintw(worldSizeY + 1, 0, size.c_str());
		mvprintw(worldSizeY + 2, 0, raport.c_str());
		mvprintw(1, worldSizeX + 2, "Y - human");
		mvprintw(2, worldSizeX + 2, "e/E - special ability(immortality)");
		mvprintw(3, worldSizeX + 2, "arrows - move");
		if(isHuman) mvprintw(4, worldSizeX + 2, "Human status: alive");
		else mvprintw(4, worldSizeX + 2, "Human status: dead");
		attroff(COLOR_PAIR(3));
	}
	else {
		mvprintw(worldSizeY + 1, 0, size.c_str());
		mvprintw(worldSizeY + 2, 0, raport.c_str());
	}

	attroff(A_BOLD);

	raport.clear();
}

void World::setInfo(std::string message) {

	raport = message;
}

void World::setZn(int zn) {
	this->zn = zn;
}

int World::getZn() {
	return zn;
}

void World::setHuman(Human* human) {

	isHuman = true;
	player = human;
}

void World::delHuman() {

	isHuman = false;
	player = nullptr;
}

bool World::ifHuman() {
	return isHuman;
}

void World::addOrganism(Organism* organism) {

	worldMap[organism->getY()][organism->getX()] = organism;
	addToQueue(organism);
}

void World::addBaby(Organism* organism) {

	worldMap[organism->getY()][organism->getX()] = organism;
	babyList.push_back(organism);
}

void World::includeBabies() {

	while (!babyList.empty()) {

		addToQueue(babyList.front());
		babyList.pop_front();
	}
}

void World::saveWorld() {

	std::fstream saveFile;
	std::string saveDest = SAVE_DIR;
	saveDest += getFileName();

	saveFile.open(saveDest.c_str(), std::ios::out);

	if (saveFile.good()) {

		saveFile << std::to_string(worldSizeX) << ' ' << std::to_string(worldSizeY) << std::endl;

		std::string organismFlat;

		for (std::list<Organism*>::iterator i = initiativeQueue.begin(), end = initiativeQueue.end(); i != end; i++) {

			organismFlat.clear();

			organismFlat = (*i)->getFlatOrganism();

			saveFile << organismFlat << std::endl;
		}

		saveFile << 'b' << std::endl;

		for (std::list<Organism*>::iterator i = babyList.begin(), end = babyList.end(); i != end; i++) {

			organismFlat.clear();

			organismFlat = (*i)->getFlatOrganism();

			saveFile << organismFlat << std::endl;
		}

		saveFile.close();
		raport = "Game saved " + saveDest + " Press any button";
		clear();
		drawWorld();
		getch();
	}
}

void World::loadWorld() {

	std::fstream loadFile;
	std::string loadDest = SAVE_DIR;
	loadDest += getFileName();

	loadFile.open(loadDest.c_str(), std::ios::in);

	if (loadFile.good()) {

		delMap();

		int sizeX, sizeY;
		loadFile >> sizeX >> sizeY;

		worldMap = new Organism**[sizeY]();
		for (int i = 0; i < sizeY; i++)worldMap[i] = new Organism*[sizeX]();

		worldSizeX = sizeX;
		worldSizeY = sizeY;

		std::string flatOrganism;

		while (!loadFile.eof()) {

			flatOrganism.clear();

			std::getline(loadFile, flatOrganism);

			if(!flatOrganism.empty() && flatOrganism != "b")deflatOrganism(flatOrganism);
			else if (flatOrganism == "b")break;
		}

		while (!loadFile.eof()) {

			flatOrganism.clear();

			std::getline(loadFile, flatOrganism);

			if (!flatOrganism.empty())deflatBaby(flatOrganism);
		}

		loadFile.close();
		raport = "Game loaded " + loadDest + ". Press any button";
		clear();
		drawWorld();
		getch();
	}
	else {
		int row, col;
		getmaxyx(stdscr, row, col);
		clear();
		mvprintw(row / 2, (col - strlen("Wrong file.")) / 2, "%s", "Wrong file.");
		getch();
	}

}

std::string World::getFileName() {

	std::string saveDest;
	char buffor[256];
	int row, col;
	getmaxyx(stdscr, row, col);

	clear();
	mvprintw(row / 2, (col - strlen("Type in save file name: ")) / 2, "%s", "Type in save file name: ");

	echo();
	getstr(buffor);
	noecho();

	saveDest = buffor;

	return saveDest;
}

void World::deflatOrganism(std::string flatOrganism) {

	std::stringstream tempOrg;

	tempOrg << flatOrganism;

	char type;
	int init, stght, x, y;
	bool special;
	int turns;

	tempOrg >> type >> init >> stght >> x >> y;

	switch (type) {

	case 'Y':
		tempOrg >> special >> turns;
		addOrganism(new Human(x, y, *this, turns, special, stght));
		break;

	case 'm':
		addOrganism(new Sheep(x, y, *this, stght));
		break;

	case 'V':
		addOrganism(new Wolf(x, y, *this, stght));
		break;

	case 'g':
		addOrganism(new Grass(x, y, *this));
		break;

	case 'd':
		addOrganism(new Dandelion(x, y, *this));
		break;

	case 'f':
		addOrganism(new Fox(x, y, *this, stght));
		break;

	case 'O':
		addOrganism(new Tortoise(x, y, *this, stght));
		break;

	case 'b':
		addOrganism(new Guarana(x, y, *this));
		break;

	case 'N':
		addOrganism(new DeadlyNightshade(x, y, *this));
		break;

	case 'Q':
		addOrganism(new HeracleumSosnowskyi(x, y, *this));
		break;

	case 'A':
		addOrganism(new Antelope(x, y, *this, stght));
		break;
	}
}

void World::deflatBaby(std::string flatOrganism) {

	std::stringstream tempOrg;

	tempOrg << flatOrganism;

	char type;
	int init, stght, x, y;
	bool special;
	int turns;

	tempOrg >> type >> init >> stght >> x >> y;

	switch (type) {

	case 'm':
		addBaby(new Sheep(x, y, *this, stght));
		break;

	case 'V':
		addBaby(new Wolf(x, y, *this, stght));
		break;

	case 'g':
		addBaby(new Grass(x, y, *this));
		break;

	case 'd':
		addBaby(new Dandelion(x, y, *this));
		break;

	case 'f':
		addBaby(new Fox(x, y, *this, stght));
		break;

	case 'O':
		addBaby(new Tortoise(x, y, *this, stght));
		break;

	case 'b':
		addBaby(new Guarana(x, y, *this));
		break;

	case 'N':
		addBaby(new DeadlyNightshade(x, y, *this));
		break;

	case 'Q':
		addBaby(new HeracleumSosnowskyi(x, y, *this));
		break;

	case 'A':
		addBaby(new Antelope(x, y, *this, stght));
		break;
	}
}

void World::delMap() {

	isHuman = false;
	raport.clear();

	if (worldMap != nullptr) {

		for (int i = 0; i < worldSizeY; i++) {

			for (int j = 0; j < worldSizeX; j++)delete worldMap[i][j];

			delete[] worldMap[i];
		}

		delete[] worldMap;
	}

	initiativeQueue.clear();
	babyList.clear();
}