#pragma once
#include "stat.h"
#include <string>
class C_STATUS_EFFECT
{
private:
	int nTurnMax;
	std::string szName;
	C_STAT cScale;
	bool bStackablity;
public:
	void setStatusEffect(int _turns, const std::string& _name, std::vector<float> _stats, bool _stack = false);
	C_STAT getScale();
	const std::string& getName();
	int getTurns();
	bool isStackable();
};
