#include "skill.h"
#include "skillmgr.h"
#include "playerclassmgr.h"
#include "passive.h"
#include <iostream>

C_SKILL::C_SKILL() :
	pNext{}, cScale{}, szName{}, szExplained{}, fHealthCost{}, fManaCost{}, nRequiredLevel{}, eSkillTarget{}, eSkillType{}
{
}

C_SKILL::~C_SKILL()
{
}

void C_SKILL::setSkill(const std::string& _name, const std::string& _detail, const std::vector<float>& _stats, int _lvl, float _hc, float _mc, E_TARGET _target, E_AFFECTTYPE _type, C_SKILL* _pNext)
{
	szName = _name;
	szExplained = _detail;
	cScale = _stats;
	pNext = _pNext;
	nRequiredLevel = _lvl;
	fHealthCost = _hc;
	fManaCost = _mc;
	eSkillTarget = _target;
	eSkillType = _type;
}

C_STAT& C_SKILL::getScale()
{
	return cScale;
}

float C_SKILL::getHealthCost()
{
	return fHealthCost;
}

float C_SKILL::getManaCost()
{
	return fManaCost;
}

int C_SKILL::getRequiredLevel()
{
	return nRequiredLevel;
}

const std::string& C_SKILL::getName()
{
	return szName;
}

const std::string& C_SKILL::getDetail()
{
	return szExplained;
}

C_SKILL::E_TARGET C_SKILL::getTarget()
{
	return eSkillTarget;
}

bool C_SKILL::hasEnoughCost(C_UNIT& _caster, float _hc, float _mc)
{
	if (_mc >= _caster.getUnitStats().getStat(C_STAT::E_STAT::CurrentMana))
	{
		std::cout << "스킬 소모MP가 현재MP보다 많습니다." << std::endl;
		return false;
	}
	if (_hc >= _caster.getUnitStats().getStat(C_STAT::E_STAT::CurrentHealth))
	{
		std::cout << "스킬 소모HP가 현재HP보다 많습니다." << std::endl;
		return false;
	}
	return true;
}

bool C_SKILL::isTargetValid(C_UNIT& _caster, C_UNIT& _target)
{
	switch (eSkillTarget)
	{
	case E_TARGET::Ally:
		return (_caster.getForce() == _target.getForce());
	case E_TARGET::Foe:
		return (_caster.getForce() != _target.getForce());
	default:
		return false;
	}
}


float C_SKILL::skillAmount(C_UNIT& _caster, C_UNIT& _target)
{
	float fAmount{};
	for (int i = 0; i < C_STAT::E_STAT::StatsMax; i++)
	{
		if (i == C_STAT::E_STAT::AttackPower || i == C_STAT::E_STAT::MagicPower || i == C_STAT::E_STAT::MaxMana || i == C_STAT::E_STAT::CurrentMana)
			fAmount += (_caster.getUnitStats().getStats()[i] + _caster.getEffectStats().getStats()[i]) * cScale.getStats()[i];
		else if (i == C_STAT::E_STAT::Armor || i == C_STAT::E_STAT::MagicResistance || i == C_STAT::E_STAT::MaxHealth || i == C_STAT::E_STAT::CurrentHealth)
			fAmount += (_target.getUnitStats().getStats()[i] + _target.getEffectStats().getStats()[i]) * cScale.getStats()[i];
	};
	return fAmount;
}

void C_SKILL::useSkill(C_UNIT& _caster, C_UNIT& _target)
{
	float fModifiedHealthCost = fHealthCost;
	float fModifiedManaCost = fManaCost;
	if (_caster.getClass() && _caster.getClass()->getPassive())
	{
		_caster.getClass()->getPassive()->callPassive(C_PASSIVE::E_CONDITION::HealthCost, _caster, _target, fModifiedHealthCost);
		_caster.getClass()->getPassive()->callPassive(C_PASSIVE::E_CONDITION::ManaCost, _caster, _target, fModifiedManaCost);
	}
	if (hasEnoughCost(_caster, fModifiedHealthCost, fModifiedManaCost) && isTargetValid(_caster, _target))
	{
		std::cout << _caster.getName() << "(이)가 " << szName << "을(를) " << _target.getName() << "에게 시전!" << std::endl;
		float fAmount = skillAmount(_caster, _target);
		doAffect(_caster, _target, fAmount);
		_caster.changeHealth(-fModifiedHealthCost);
		_caster.changeMana(-fModifiedManaCost);

		if (pNext)
			pNext->useSkill(_caster, _target);

		return;
	}
	std::cout << "스킬 사용에 실패했습니다." << std::endl;
}

bool C_SKILL::hasNext()
{
	if (pNext)
		return true;
	return false;
}

void C_SKILL::doAffect(C_UNIT& _caster, C_UNIT& _target, float _amount)
{
	(this->*C_SKILLMGR::fpAffect[static_cast<int>(eSkillType)])(_caster, _target, _amount);
}

void C_SKILL::doBasicAttack(C_UNIT& _attacker, C_UNIT& _defender, float _amount)
{
	if (_attacker.getClass() && _attacker.getClass()->getPassive() &&
		_attacker.getClass()->getPassive()->callPassive(C_PASSIVE::E_CONDITION::BasicAttack, _attacker, _defender, _amount));

	else doDamage(_attacker, _defender, _amount);
}

void C_SKILL::doDamage(C_UNIT& _attacker, C_UNIT& _defender, float _amount)
{
	if (_amount < 0)
		_amount = 0;
	_defender.changeHealth(-_amount);

	std::cout << _attacker.getName() << "(이)가 " << _defender.getName() << "에게 " << _amount << "만큼의 피해를 주었습니다." << std::endl;
	if (_defender.getClass() && _defender.getClass()->getPassive() &&
		_defender.getClass()->getPassive()->callPassive(C_PASSIVE::E_CONDITION::TakeDamage, _defender, _attacker, _amount));
}

void C_SKILL::doHeal(C_UNIT& _healer, C_UNIT& _target, float _amount)
{
	_target.changeHealth(_amount);

	std::cout << _healer.getName() << "(이)가 " << _target.getName() << "에게 " << _amount << "만큼의 피해를 회복해 주었습니다." << std::endl;
}

void C_SKILL::doManaRestoration(C_UNIT& _restorer, C_UNIT& _target, float _amount)
{
	_target.changeMana(_amount);

	std::cout << _restorer.getName() << "(이)가 " << _target.getName() << "에게 " << _amount << "만큼의 마나를 회복해 주었습니다." << std::endl;
}