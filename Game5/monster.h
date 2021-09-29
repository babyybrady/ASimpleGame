#pragma once
#include "unit.h"
#include "effectskill.h"

class C_MONSTER : public C_UNIT
{
private:
	C_STAT cGrowth;
public:
	C_MONSTER();
	void setMonster(std::string& _name, const std::vector<float>& _stats, const std::vector<float>& _gs, E_FORCE _fc, C_UNIT_CLASS* _class);
	void printMonster();
	float getExpFromMonster();
	void spawnMonster(std::string& _newname, C_UNIT_CLASS* _class);
};