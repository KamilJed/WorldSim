#pragma once
#include "Animal.h"
class Human :
	public Animal
{
	bool special;
	int turnsRemaining;
public:
	Human(int, int, World&);
	Human(int, int, World&, int, bool, int);
	~Human();
	void draw();
	bool action();
	Organism* clone(int, int);
	bool getSpecial();
	int getTurns();
	std::string getFlatOrganism();
	bool escape(int, int);
	bool collision(Organism*, int, int);
	void abilityControl();
};

