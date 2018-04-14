#pragma once
#include "Animal.h"
class Sheep :
	public Animal
{
public:
	Sheep(int, int, World&);
	Sheep(int, int, World&, int);
	~Sheep();
	Organism* clone(int, int);
};

