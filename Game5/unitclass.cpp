#include "unitclass.h"
#include "unit.h"
#include "passive.h"
#include <iostream>


C_UNIT_CLASS::C_UNIT_CLASS() :
	szName{}, cBasic{}, pPassive{}
{
}

C_UNIT_CLASS::~C_UNIT_CLASS()
{
}

void C_UNIT_CLASS::changeClass(C_UNIT& _unit)
{
	_unit.changeClass(this);
}

void C_UNIT_CLASS::setUnitClass(const std::string& _name, const std::vector<float>& _bs, C_PASSIVE* _passive)
{
	szName = _name;
	cBasic = _bs;
	pPassive = _passive;
}

const std::string& C_UNIT_CLASS::getName()
{
	return szName;
}

C_STAT& C_UNIT_CLASS::getBasicStats()
{
	return cBasic;
}

C_PASSIVE* C_UNIT_CLASS::getPassive()
{
	return pPassive;
}

C_STAT& C_UNIT_CLASS::getGrowthStats()
{
	return cBasic;
}

void C_UNIT_CLASS::growUp(C_UNIT* _unit)
{
}
