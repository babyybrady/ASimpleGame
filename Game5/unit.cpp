#include "unit.h"
#include "effectskill.h"
#include <iostream>

C_UNIT::C_UNIT() :
	szName{}, cUnitStats{}, cEffectStats{}, unitForce{}, listStatusEffect{}, pUnitSkills{}
{
}

void C_UNIT::setUnit(const std::string& _name, const std::vector<float>& _stats, E_FORCE _fc, C_UNIT_CLASS* _class)
{
	szName = _name;
	unitForce = _fc;
	cUnitStats = _stats;
	pClass = _class;
	cEffectStats.getStats().resize(C_STAT::E_STAT::StatsMax);
	restoreResources();
}

C_STAT& C_UNIT::getUnitStats()
{
	return cUnitStats;
}

C_STAT& C_UNIT::getEffectStats()
{
	return cEffectStats;
}

C_UNIT_CLASS* C_UNIT::getClass()
{
	return pClass;
}

const std::string& C_UNIT::getName()
{
	return szName;
}

C_UNIT::E_FORCE C_UNIT::getForce()
{
	return unitForce;
}

void C_UNIT::changeClass(C_UNIT_CLASS* _class)
{
	pClass = _class;
}

void C_UNIT::changeHealth(float _health)
{
	cUnitStats.addStat(C_STAT::E_STAT::CurrentHealth, _health);
	resetHP();
}

void C_UNIT::changeMana(float _mana)
{
	cUnitStats.addStat(C_STAT::E_STAT::CurrentMana, _mana);
	resetMP();
}
bool C_UNIT::forgetSkill(size_t _slot)
{
	pUnitSkills[_slot] = nullptr;
	return true;
}

bool C_UNIT::learnSkill(C_SKILL* _skill, size_t _slot)
{
	if (pUnitSkills[_slot] && !forgetSkill(_slot))
		return false;
	pUnitSkills[_slot] = _skill;
	return true;
}

void C_UNIT::recoverHP()
{
	cUnitStats.setStat(C_STAT::E_STAT::CurrentHealth, cUnitStats.getStat(C_STAT::E_STAT::MaxHealth) 
		+ cEffectStats.getStat(C_STAT::E_STAT::MaxHealth));
}

void C_UNIT::recoverMP()
{
	cUnitStats.setStat(C_STAT::E_STAT::CurrentMana, cUnitStats.getStat(C_STAT::E_STAT::MaxMana) 
		+ cEffectStats.getStat(C_STAT::E_STAT::MaxMana));
}

void C_UNIT::resetHP()
{
	if (cUnitStats.getStat(C_STAT::E_STAT::CurrentHealth) > cUnitStats.getStat(C_STAT::E_STAT::MaxHealth) 
		+ cEffectStats.getStat(C_STAT::E_STAT::MaxHealth))
		recoverHP();
}

void C_UNIT::resetMP()
{
	if (cUnitStats.getStat(C_STAT::E_STAT::CurrentMana) > cUnitStats.getStat(C_STAT::E_STAT::MaxMana) +
		cEffectStats.getStat(C_STAT::E_STAT::MaxMana))
		recoverMP();
}

void C_UNIT::restoreResources()
{
	recoverHP();
	recoverMP();
}

void C_UNIT::resetResources()
{
	resetHP();
	resetMP();
}

void C_UNIT::initiateStatusEffects()
{
	for (int i = 0; i < C_STAT::E_STAT::StatsMax; i++)
	{
		cEffectStats.setStat(static_cast<C_STAT::E_STAT>(i), 0);
	}
	for (std::list<S_NODE*>::iterator iter = listStatusEffect.begin(); iter != listStatusEffect.end(); iter++)
	{
		changeHealth(cUnitStats.getStat(C_STAT::E_STAT::CurrentHealth) * (*iter)->pStatusEffect->getScale().getStat(C_STAT::E_STAT::MaxHealth));
		changeMana(cUnitStats.getStat(C_STAT::E_STAT::CurrentMana) * (*iter)->pStatusEffect->getScale().getStat(C_STAT::E_STAT::MaxMana));
		cEffectStats += cUnitStats * (*iter)->pStatusEffect->getScale();
	}
}

void C_UNIT::terminateStatusEffects()
{
	if (cEffectStats.getStat(C_STAT::E_STAT::CurrentHealth) > 0)
	{
		changeHealth(cEffectStats.getStat(C_STAT::E_STAT::CurrentHealth));
		std::cout << szName << "(이)가 체력재생 효과를 받아 체력을 " << cEffectStats.getStat(C_STAT::E_STAT::CurrentHealth) << "만큼 회복했습니다." << std::endl;
	}
	if (cEffectStats.getStat(C_STAT::E_STAT::CurrentMana) > 0)
	{
		changeMana(cEffectStats.getStat(C_STAT::E_STAT::CurrentMana));
		std::cout << szName << "(이)가 마력재생 효과를 받아 마력을 " << cEffectStats.getStat(C_STAT::E_STAT::CurrentMana) << "만큼 회복했습니다." << std::endl;
	}
	std::list<S_NODE*>::iterator iter = listStatusEffect.begin();
	while (iter != listStatusEffect.end())
	{
		if ((*iter)->nTurnRemaining > 0)
			(*iter)->nTurnRemaining--;
		if ((*iter)->nTurnRemaining == 0)
		{
			delete* iter;
			iter = listStatusEffect.erase(iter);
		}
		else iter++;
	};
}

void C_UNIT::printStatusEffects()
{
	int nCount{ 1 };
	for (S_NODE* pNode : listStatusEffect)
	{
		std::cout << szName << "의 " << nCount << "번째 상태 : " << pNode->pStatusEffect->getName() << "(" << pNode->nTurnRemaining << "턴 남음)" << std::endl;
		nCount++;
	}
}

void C_UNIT::printUnit()
{
	std::cout << "이름 : " << szName << std::endl;
	std::cout << "체력 : " << cUnitStats.getStat(C_STAT::E_STAT::CurrentHealth) << " / " << cUnitStats.getStat(C_STAT::E_STAT::MaxHealth) 
		<< " (+" << cEffectStats.getStat(C_STAT::E_STAT::MaxHealth) << ")\t| 마력 : " << cUnitStats.getStat(C_STAT::E_STAT::CurrentMana) << " / " 
		<< cUnitStats.getStat(C_STAT::E_STAT::MaxMana) << " (+" << cEffectStats.getStat(C_STAT::E_STAT::MaxMana) << ")" << std::endl;
	std::cout << "공격력 : " << cUnitStats.getStat(C_STAT::E_STAT::AttackPower) << " (+" << cEffectStats.getStat(C_STAT::E_STAT::AttackPower) 
		<< ")\t| 마법공격력 : " << cUnitStats.getStat(C_STAT::E_STAT::MagicPower) << " (+" << cEffectStats.getStat(C_STAT::E_STAT::MagicPower) << ")" << std::endl;
	std::cout << "방어력 : " << cUnitStats.getStat(C_STAT::E_STAT::Armor) << " (+" << cEffectStats.getStat(C_STAT::E_STAT::Armor) << ")\t| 마법저항력 : " 
		<< cUnitStats.getStat(C_STAT::E_STAT::MagicResistance) << " (+" << cEffectStats.getStat(C_STAT::E_STAT::MagicResistance) << ")" << std::endl;
	printStatusEffects();
}

void C_UNIT::printSkills()
{
	for (int i = 0; i < SlotsMax; i++)
	{
		if (pUnitSkills[i])
			std::cout << "슬롯 " << i << ": " << pUnitSkills[i]->getName() << std::endl << pUnitSkills[i]->getDetail() << std::endl;
	}
}

void C_UNIT::useSkillBySlot(int _slot, C_UNIT& _target)
{
	if (!pUnitSkills[_slot])
	{
		printf("스킬 슬롯이 비었습니다.\n");
		return;
	}
	pUnitSkills[_slot]->useSkill(*this, _target);
}
