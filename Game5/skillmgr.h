#pragma once
#include <map>
#include <string>
#include "skill.h"

class C_SKILLMGR
{
private:
	static std::map<std::string, C_SKILL*> mapSkill;

public:
	static void (C_SKILL::* fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::AffectMax)])(C_UNIT&, C_UNIT&, float);

public:
	C_SKILLMGR() = delete;
	static void loadData();
	static void clearData();
	static C_SKILL* findSkill(const std::string& _name);
};

