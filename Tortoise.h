#pragma once
#include "Animal.h"
class Tortoise :
	public Animal
{
public:
	Tortoise(int, int, World&);
	Tortoise(int, int, World&, int);
	~Tortoise();
	bool action();
	bool collision(Organism*, int, int);
	Organism* clone(int, int);
	bool deflectAttack(Organism*);
};

