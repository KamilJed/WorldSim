#pragma once
#include "Plant.h"
class Dandelion :
	public Plant
{
public:
	Dandelion(int, int, World&);
	~Dandelion();
	bool action();
	Organism* clone(int, int);
};

