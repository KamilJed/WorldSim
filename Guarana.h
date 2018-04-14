#pragma once
#include "Plant.h"
class Guarana :
	public Plant
{
public:
	Guarana(int, int, World&);
	~Guarana();
	int boost();
	Organism* clone(int, int);
};

