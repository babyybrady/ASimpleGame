#include "statuseffect.h"
#include <iostream>

void C_STATUS_EFFECT::setStatusEffect(int _turns, const std::string& _name, std::vector<float> _stats, bool _stack)
{
	szName = _name;
	nTurnMax = _turns;
	bStackablity = _stack;
	cScale = _stats;
}

C_STAT C_STATUS_EFFECT::getScale()
{
	return cScale;
}

const std::string& C_STATUS_EFFECT::getName()
{
	return szName;
}

int C_STATUS_EFFECT::getTurns()
{
	return nTurnMax;
}

bool C_STATUS_EFFECT::isStackable()
{
	return bStackablity;
}
