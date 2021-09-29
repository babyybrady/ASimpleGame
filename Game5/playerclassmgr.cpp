#include "playerclassmgr.h"
#include "passivemgr.h"
#include "playerclass.h"
#include "skillmgr.h"

std::map<std::string, C_PLAYER_CLASS*> C_PLAYERCLASSMGR::mapPlayerClass{};

void C_PLAYERCLASSMGR::loadData()
{
	std::vector<float> vBasic{};
	std::vector<float> vGrowth{};
	vBasic.reserve(C_STAT::E_STAT::StatsMax);
	vGrowth.reserve(C_STAT::E_STAT::StatsMax);
	
	std::map<int, C_SKILL*> mapClassSkill{};
	std::map<int, C_PLAYER_CLASS*> mapSubclass{};

	C_PLAYER_CLASS* pWarrior = new C_PLAYER_CLASS{};
	vBasic = { 150, 5, 7, 5, 3, 3, 0, 0 };
	vGrowth = { 50, 3, 5, 3, 1, 1, 0, 0 };

	pWarrior->setPlayerClass("Warrior", vBasic, C_PASSIVEMGR::findPassive("CombatMaster"), vGrowth, mapClassSkill, mapSubclass);

	C_PLAYER_CLASS* pMagician = new C_PLAYER_CLASS{};
	vBasic = { 50, 50, 3, 5, 7, 5, 0, 0 };
	vGrowth = { 20, 20, 1, 3, 5, 3, 0, 0 };

	pMagician->setPlayerClass("Magician", vBasic, C_PASSIVEMGR::findPassive("MagicMaster"), vGrowth, mapClassSkill, mapSubclass);

	C_PLAYER_CLASS* pBeginner = new C_PLAYER_CLASS{};
	vBasic = { 75, 15, 2, 0, 2, 0, 0, 0 };
	vGrowth = { 25, 5, 3, 2, 3, 2, 0, 0 };

	mapClassSkill.insert(std::pair<int, C_SKILL*>(2, C_SKILLMGR::findSkill("FireBall")));
	mapClassSkill.insert(std::pair<int, C_SKILL*>(3, C_SKILLMGR::findSkill("SelfHeal")));
	mapClassSkill.insert(std::pair<int, C_SKILL*>(5, C_SKILLMGR::findSkill("Reinforcement")));
	mapClassSkill.insert(std::pair<int, C_SKILL*>(7, C_SKILLMGR::findSkill("TripleAttack")));
	mapSubclass.insert(std::pair<int, C_PLAYER_CLASS*>(10, pWarrior));
	mapSubclass.insert(std::pair<int, C_PLAYER_CLASS*>(11, pMagician));
	
	pBeginner->setPlayerClass("Beginner", vBasic, C_PASSIVEMGR::findPassive("NoPassive"), vGrowth, mapClassSkill, mapSubclass);
	mapPlayerClass.insert(std::pair<std::string, C_PLAYER_CLASS*>("Beginner", pBeginner));

	mapClassSkill.clear();
	mapSubclass.clear();
}

void C_PLAYERCLASSMGR::clearData()
{
	for (std::pair<std::string, C_PLAYER_CLASS*> pair : mapPlayerClass)
	{
		C_PLAYER_CLASS* pPlayerClass = pair.second;
		delete pPlayerClass;
	}
	mapPlayerClass.clear();
}

C_PLAYER_CLASS* C_PLAYERCLASSMGR::findPlayerClass(const std::string& _name)
{
	std::map<std::string, C_PLAYER_CLASS*>::iterator iter = mapPlayerClass.find(_name);
	if (iter == mapPlayerClass.end())
		return nullptr;
	return iter->second;
}