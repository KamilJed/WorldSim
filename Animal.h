#pragma once
#include "Organism.h"
class Animal :
	public Organism
{
public:
	Animal(int, int, World&);
	Animal(int, int, World&, int);
	virtual ~Animal();
	virtual void draw();
	virtual bool action();
	virtual bool collision(Organism*, int, int);
	virtual bool escape(int, int);
};

