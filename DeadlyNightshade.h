#pragma once
#include "Plant.h"
class DeadlyNightshade :
	public Plant
{
public:
	DeadlyNightshade(int, int, World&);
	~DeadlyNightshade();
	bool isPoisonous();
	Organism* clone(int, int);
};

