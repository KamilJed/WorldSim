#pragma once
#include "Animal.h"
class Fox :
	public Animal
{
public:
	Fox(int , int, World&);
	Fox(int, int, World&, int);
	~Fox();
	bool action();
	Organism* clone(int, int);
};

