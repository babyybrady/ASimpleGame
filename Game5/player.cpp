#include "player.h"
#include "monster.h"
#include "effectskill.h"
#include "playerclass.h"
#include <iostream>

C_PLAYER::C_PLAYER() :
	C_UNIT(), nLevel{}, fExp{}, fRequiredExp{}
{
}

void C_PLAYER::setPlayer(std::string& _name, E_FORCE _fc, C_PLAYER_CLASS* _class, int _level, float _exp)
{
	C_STAT cStat = _class->getBasicStats() + _class->getGrowthStats() * _level;
	setUnit(_name, cStat.getStats(), _fc, _class);
	nLevel = _level;
	fExp = _exp;
	fRequiredExp = static_cast<float>(nLevel * 100);
}

int C_PLAYER::getLevel()
{
	return nLevel;
}

void C_PLAYER::changeClass(C_PLAYER_CLASS* _class)
{
	C_UNIT::pClass = _class;
	pClass = _class;
	cUnitStats = _class->getBasicStats() + _class->getGrowthStats() * nLevel;
}
bool C_PLAYER::forgetSkill(size_t _slot)
{
	if (!pUnitSkills[_slot])
		return true;
	std::cout << _slot << "�� ���Կ� ��ų " << pUnitSkills[_slot]->getName() << "��(��) ��ϵǾ��ֽ��ϴ�." << std::endl;
	std::cout << "��ų�� ����ðڽ��ϱ�?(0: No, 1: Yes) >> ";
	int nInput{};
	nInput = inputInt(0, 1);
	if (nInput == 0)
	{
		std::cout << "��ų ����⸦ ����ϼ̽��ϴ�." << std::endl;
		return false;
	}
	std::cout << _slot << "�� ���Կ� ��ų " << pUnitSkills[_slot]->getName() << "��(��) ���������� �����Ǿ����ϴ�." << std::endl;
	std::cout << "==================================================" << std::endl;
return C_UNIT::forgetSkill(_slot);
}
bool C_PLAYER::learnSkill(C_SKILL* _skill, size_t _slot)
{
	if (_skill->getRequiredLevel() > nLevel)
	{
		std::cout << "��ų�� ���� ���� ������ �����մϴ�." << std::endl;
		return true;
	}
	if (!C_UNIT::learnSkill(_skill, _slot))
		return false;
	std::cout << szName << "��(��) " << _slot << "�� ���Կ� " << _skill->getName() << " ��ų�� ������ϴ�." << std::endl;
	std::cout << "==================================================" << std::endl;

	return true;
}

void C_PLAYER::printPlayer()
{
	std::cout << "���� : " << nLevel << " [ " << fExp << " / " << fRequiredExp << " ]\t���� : " << pClass->getName() << std::endl;
	printUnit();
}

void C_PLAYER::killedMonster(C_MONSTER& _monster)
{
	fExp += _monster.getExpFromMonster();
	std::cout << _monster.getName() << "��(��) óġ�߽��ϴ�." << std::endl << "����ġ�� " << _monster.getExpFromMonster() << "��ŭ �ö����ϴ�." << std::endl;

	while (fExp >= fRequiredExp)
		levelUp();
}

void C_PLAYER::levelUp()
{
	system("cls");
	std::cout << szName << "�� ������ 1 �ö����ϴ�!" << std::endl;
	std::cout << "������ ����Ͽ� ���� ���ʽ� �ɷ�ġ�� �־����ϴ�." << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "���� : " << nLevel << " [ +1 ���! ]\t���� : " << pClass->getName() << std::endl;
	std::cout << "�̸� : " << szName << std::endl;
	std::cout << "�ִ� ü�� : " << cUnitStats.getStat(C_STAT::E_STAT::MaxHealth) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MaxHealth) << ")\t| �ִ� ���� :" 
		<< cUnitStats.getStat(C_STAT::E_STAT::MaxMana) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MaxMana) << ")" << std::endl;
	std::cout << "���ݷ� : " << cUnitStats.getStat(C_STAT::E_STAT::AttackPower) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::AttackPower)
		<< ")\t| �������ݷ� : " << cUnitStats.getStat(C_STAT::E_STAT::MagicPower) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MagicPower) << ")" << std::endl;
	std::cout << "���� : " << cUnitStats.getStat(C_STAT::E_STAT::Armor) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::Armor) << ")\t| �������׷� : "
		<< cUnitStats.getStat(C_STAT::E_STAT::MagicResistance) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MagicResistance) << ")" << std::endl;
	std::cout << "==================================================" << std::endl;	fExp -= fRequiredExp;
	nLevel++;
	fRequiredExp = static_cast<float>(nLevel * 100);
	pClass->growUp(this);
	restoreResources();
	enter();
}
