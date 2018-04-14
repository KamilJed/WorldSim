#pragma once
#include "Organism.h"
class Plant :
	public Organism
{
public:
	Plant(int, int, World&);
	virtual ~Plant();
	void draw();
	virtual bool action();
	virtual int boost();
	virtual bool isPoisonous();
};

