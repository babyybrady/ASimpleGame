#include "passive.h"
#include "skillmgr.h"
#include "statuseffectmgr.h"
#include "effectskill.h"
#include <iostream>

C_PASSIVE::C_PASSIVE() :
	szName{},
	szExplained{},
	pairPassive{}
{
}

void C_PASSIVE::setPassive(const std::string& _name, const std::string& _detail, std::pair<FP_P, float>** _pair)
{
	szName = _name;
	szExplained = _detail;
	for (int i = 0; i < ConditionMax; i++)
	{
		pairPassive[i] = _pair[i];
	}
}

bool C_PASSIVE::callPassive(E_CONDITION _cd, C_UNIT& _caster, C_UNIT& _target, float& _number)
{
	if (pairPassive[_cd] && (*pairPassive[_cd]).first)
	{
		(this->*(*pairPassive[_cd]).first)((*pairPassive[_cd]).second, _caster, _target, _number);
		return true;
	}
	return false;
}

void C_PASSIVE::reflectDamage(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _damage)
{
	std::cout << _caster.getName() << "(��)�� " << _target.getName() << "���� ���� ���� �ݻ�!" << std::endl;
	C_SKILLMGR::findSkill("ReflectDamage")->doAffect(_caster, _target, _damage * _rate);
}

void C_PASSIVE::release()
{
	for (int i = 0; i < ConditionMax; i++)
	{
		if (pairPassive[i])
			delete pairPassive[i];
	}
}

void C_PASSIVE::lifesteal(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _damage)
{
	C_SKILLMGR::findSkill("BasicAttack")->doAffect(_caster, _target);
	std::cout << _caster.getName() << "(��)�� " << _target.getName() << "���� �� ���� ���!" << std::endl;
	C_SKILLMGR::findSkill("Lifesteal")->doAffect(_caster, _caster, _damage * _rate);
}

void C_PASSIVE::magicBasic(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _damage)
{
	float fPhysical{};
	float fMagical{};
	if (1 - _rate > 0)
	{
		fPhysical = _damage * (1 - _rate);
		C_SKILLMGR::findSkill("BasicAttack")->doDamage(_caster, _target, fPhysical);
	}
	if (_rate > 0)
	{
		C_SKILL* pBasicMagic = C_SKILLMGR::findSkill("BasicMagic");
		fMagical = pBasicMagic->skillAmount(_caster, _target) * _rate;
		std::cout << _caster.getName() << "�� �⺻������ ������������ ��ȯ�˴ϴ�." << std::endl;
		pBasicMagic->doAffect(_caster, _target, fMagical);}
	_damage = fPhysical + fMagical;
}

void C_PASSIVE::reduceHealthCost(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _cost)
{
	std::cout << _caster.getName() << "�� ü�� �Ҹ��� " << 100 * _rate << "% �����մϴ�." << std::endl;
	_cost *= 1 - _rate;
}

void C_PASSIVE::reduceManaCost(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _cost)
{
	std::cout << _caster.getName() << "�� ���� �Ҹ��� " << 100 * _rate << "% �����մϴ�." << std::endl;
	_cost *= 1 - _rate;
}
