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
	std::cout << _slot << "번 슬롯에 스킬 " << pUnitSkills[_slot]->getName() << "이(가) 등록되어있습니다." << std::endl;
	std::cout << "스킬을 지우시겠습니까?(0: No, 1: Yes) >> ";
	int nInput{};
	nInput = inputInt(0, 1);
	if (nInput == 0)
	{
		std::cout << "스킬 지우기를 취소하셨습니다." << std::endl;
		return false;
	}
	std::cout << _slot << "번 슬롯에 스킬 " << pUnitSkills[_slot]->getName() << "이(가) 성공적으로 삭제되었습니다." << std::endl;
	std::cout << "==================================================" << std::endl;
return C_UNIT::forgetSkill(_slot);
}
bool C_PLAYER::learnSkill(C_SKILL* _skill, size_t _slot)
{
	if (_skill->getRequiredLevel() > nLevel)
	{
		std::cout << "스킬을 배우기 위한 레벨이 부족합니다." << std::endl;
		return true;
	}
	if (!C_UNIT::learnSkill(_skill, _slot))
		return false;
	std::cout << szName << "이(가) " << _slot << "번 슬롯에 " << _skill->getName() << " 스킬을 배웠습니다." << std::endl;
	std::cout << "==================================================" << std::endl;

	return true;
}

void C_PLAYER::printPlayer()
{
	std::cout << "레벨 : " << nLevel << " [ " << fExp << " / " << fRequiredExp << " ]\t직업 : " << pClass->getName() << std::endl;
	printUnit();
}

void C_PLAYER::killedMonster(C_MONSTER& _monster)
{
	fExp += _monster.getExpFromMonster();
	std::cout << _monster.getName() << "을(를) 처치했습니다." << std::endl << "경험치가 " << _monster.getExpFromMonster() << "만큼 올랐습니다." << std::endl;

	while (fExp >= fRequiredExp)
		levelUp();
}

void C_PLAYER::levelUp()
{
	system("cls");
	std::cout << szName << "의 레벨이 1 올랐습니다!" << std::endl;
	std::cout << "레벨이 상승하여 직업 보너스 능력치가 주어집니다." << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "레벨 : " << nLevel << " [ +1 상승! ]\t직업 : " << pClass->getName() << std::endl;
	std::cout << "이름 : " << szName << std::endl;
	std::cout << "최대 체력 : " << cUnitStats.getStat(C_STAT::E_STAT::MaxHealth) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MaxHealth) << ")\t| 최대 마력 :" 
		<< cUnitStats.getStat(C_STAT::E_STAT::MaxMana) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MaxMana) << ")" << std::endl;
	std::cout << "공격력 : " << cUnitStats.getStat(C_STAT::E_STAT::AttackPower) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::AttackPower)
		<< ")\t| 마법공격력 : " << cUnitStats.getStat(C_STAT::E_STAT::MagicPower) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MagicPower) << ")" << std::endl;
	std::cout << "방어력 : " << cUnitStats.getStat(C_STAT::E_STAT::Armor) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::Armor) << ")\t| 마법저항력 : "
		<< cUnitStats.getStat(C_STAT::E_STAT::MagicResistance) << " (+" << pClass->getGrowthStats().getStat(C_STAT::E_STAT::MagicResistance) << ")" << std::endl;
	std::cout << "==================================================" << std::endl;	fExp -= fRequiredExp;
	nLevel++;
	fRequiredExp = static_cast<float>(nLevel * 100);
	pClass->growUp(this);
	restoreResources();
	enter();
}
