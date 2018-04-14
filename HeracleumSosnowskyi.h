#pragma once
#include "Plant.h"
class HeracleumSosnowskyi :
	public Plant
{
public:
	HeracleumSosnowskyi(int, int, World&);
	~HeracleumSosnowskyi();
	bool isPoisonous();
	Organism* clone(int, int);
	bool action();
};

