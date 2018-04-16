#pragma once

#include <list>
#include <string>

#define ESC 27
#define BACKSPACE '\b'
#define ENTER '\n'
#define SAVE_DIR "games/"

class Organism;
class Human;

class World
{
	std::list<Organism*> initiativeQueue;
	std::list<Organism*> babyList;
	std::list<Organism*>::iterator iter;
	Organism ***worldMap;
	Human* player;
	int worldSizeX, worldSizeY;
	int zn;
	bool isHuman;
	int turn;
	std::string raport;

public:
	World(int, int);
	~World();
	void newTurn();
	void drawWorld();
	Organism *isEmpty(int, int);
	void erase(Organism*);
	int getSizeX();
	int getSizeY();
	void set(Organism*);
	void unset(int, int);
	void addToQueue(Organism*);
	void info();
	void setInfo(std::string);
	int getZn();
	void setZn(int);
	void setHuman(Human*);
	bool ifHuman();
	void addOrganism(Organism*);
	void includeBabies();
	void addBaby(Organism*);
	void saveWorld();
	void loadWorld();
	std::string getFileName();
	void deflatOrganism(std::string);
	void deflatBaby(std::string);
	void delMap();
};

