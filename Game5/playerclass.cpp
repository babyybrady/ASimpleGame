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
	std::cout << "������ �ö� ���ο� ���� " << pSubclass->szName << "(��)�� ������ �� �ֽ��ϴ�." << std::endl;
	std::cout << "�����Ͻðڽ��ϱ�?(0: No, 1: Yes) >> ";
	int nInput{};
	nInput = inputInt(0, 1);
	if (nInput == 0)
	{
		std::cout << "������ �����ϼ̽��ϴ�. �ٸ� �������� ������ �����մϴ�." << std::endl;
		return;
	}
	_player.changeClass(pSubclass);
	std::cout << "������ " << pSubclass->szName << "(��)�� ������ �����ϼ̽��ϴ�." << std::endl;
	std::cout << "���ο� ������ �µ��� �ɷ�ġ�� ���� �Ǿ����ϴ�." << std::endl;
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
		std::cout << "������ �ö� ���ο� ��ų " << pLevelSkill->getName() << "��(��) ��� �� �ְ� �Ǿ����ϴ�." << std::endl;
		std::cout << "==================================================" << std::endl;
		std::cout << "���ο� ��ų�� ��� ������ �����ϼ���.[0 ~ 9] >> ";
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
