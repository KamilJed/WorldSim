#pragma once
#include <list>

class World;

class Organism
{

protected:
	int strength;
	int initiative;
	int posX, posY;
	char icon;
	World *world;
public:

	Organism();
	Organism(int, int, World&);
	Organism(int, int, World&, int);
	virtual ~Organism();
	int getX();
	int getY();
	int getStrength();
	int getInitiative();
	virtual void draw();
	virtual bool action() = 0;
	virtual bool collision(Organism*, int, int);
	char getIcon();
	virtual Organism* clone(int, int) = 0;
	virtual bool deflectAttack(Organism*);
	virtual std::string getFlatOrganism();
	virtual bool getSpecial();
};

