#pragma once
#include "Animal.h"
class Wolf :
	public Animal
{
public:
	Wolf(int, int, World&);
	Wolf(int, int, World&, int);
	~Wolf();
	Organism* clone(int, int);
};

