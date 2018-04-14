#pragma once
#include "Plant.h"
class Grass :
	public Plant
{
public:
	Grass(int, int, World&);
	~Grass();
	Organism* clone(int, int);
};

