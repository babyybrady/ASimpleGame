#include "playerclass.h"
#include "player.h"
#include <iostream>

C_PLAYER_CLASS::C_PLAYER_CLASS() :
	C_UNIT_CLASS{}, cGrowth{}, mapClassSkill{}, mapSubclass{}
{
}

void C_PLAYER_CLASS::setPlayerClass(const std::string& _name, const std::vector<float>& _bs, C_PASSIVE* _passive, const std::vector<float>& _gs,
	const std::map<int, C_SKILL*> _cs, const std::map<int, C_PLAYER_CLASS*> _sc)
{
	setUnitClass(_name, _bs, _passive);
	mapClassSkill = _cs;
	mapSubclass = _sc;
	cGrowth = _gs;
}

void C_PLAYER_CLASS::changeSubclass(C_PLAYER& _player)
{
	std::map<int, C_PLAYER_CLASS*>::iterator iter = mapSubclass.find(_player.getLevel());
	if (iter == mapSubclass.end())
		return;
	C_PLAYER_CLASS* pSubclass{};
	pSubclass = iter->second;
	std::cout << "레벨이 올라 새로운 직업 " << pSubclass->szName << "(으)로 전직할 수 있습니다." << std::endl;
	std::cout << "전직하시겠습니까?(0: No, 1: Yes) >> ";
	int nInput{};
	nInput = inputInt(0, 1);
	if (nInput == 0)
	{
		std::cout << "전직을 포기하셨습니다. 다른 직업으로 전직이 가능합니다." << std::endl;
		return;
	}
	_player.changeClass(pSubclass);
	std::cout << "신직업 " << pSubclass->szName << "(으)로 전직에 성공하셨습니다." << std::endl;
	std::cout << "새로운 직업에 맞도록 능력치가 재편성 되었습니다." << std::endl;
}

void C_PLAYER_CLASS::growUp(C_UNIT* _unit)
{
	levelUp(*dynamic_cast<C_PLAYER*>(_unit));
}

void C_PLAYER_CLASS::learnClassSkill(C_PLAYER& _player)
{
	std::map<int, C_SKILL*>::iterator iter = mapClassSkill.find(_player.getLevel());
	if (iter == mapClassSkill.end())
		return;
	C_SKILL* pLevelSkill{};
	pLevelSkill = iter->second;
	int nSlot{};
	do
	{
		std::cout << "레벨이 올라 새로운 스킬 " << pLevelSkill->getName() << "을(를) 배울 수 있게 되었습니다." << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << "새로운 스킬을 배울 슬롯을 선택하세요.[0 ~ 9] >> ";
		nSlot = inputInt(0, 9);
	} while (!_player.learnSkill(pLevelSkill, nSlot));
}


void C_PLAYER_CLASS::levelUp(C_PLAYER& _player)
{
	_player.getUnitStats() += cGrowth;
	learnClassSkill(_player);
	changeSubclass(_player);
}

C_STAT& C_PLAYER_CLASS::getGrowthStats()
{
	return cGrowth;
}
