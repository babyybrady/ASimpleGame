#include "monster.h"
#include "player.h"
#include "effectskill.h"
#include <iostream>

C_MONSTER::C_MONSTER() : 
	C_UNIT(), cGrowth{}
{
}

void C_MONSTER::setMonster(std::string& _name, const std::vector<float>& _stats, const std::vector<float>& _gs, E_FORCE _fc, C_UNIT_CLASS* _class)
{
	setUnit(_name, _stats, _fc, _class);
	cGrowth=_gs;
}

void C_MONSTER::printMonster()
{
	printUnit();
}

float C_MONSTER::getExpFromMonster()
{
	return cUnitStats.getStat(C_STAT::E_STAT::MaxHealth);
}

void C_MONSTER::spawnMonster(std::string& _newname, C_UNIT_CLASS* _class)
{
	szName.clear();
	szName = _newname;
	cUnitStats += cGrowth;
	pClass = _class;
	restoreResources();
}