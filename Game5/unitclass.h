#pragma once
#include "effectskill.h"
#include <map>
class C_UNIT;
class C_PASSIVE;

class C_UNIT_CLASS
{
protected:
	std::string szName;
	C_STAT cBasic;
	C_PASSIVE* pPassive;

private:
	void changeClass(C_UNIT& _unit);

public:
	C_UNIT_CLASS();
	virtual ~C_UNIT_CLASS();
	void setUnitClass(const std::string& _name, const std::vector<float>& _bs, C_PASSIVE* _passive);
	const std::string& getName();
	C_STAT& getBasicStats();
	C_PASSIVE* getPassive();
	virtual C_STAT& getGrowthStats();
	virtual void growUp(C_UNIT* _unit);
};

int inputInt(int _min, int _max);
