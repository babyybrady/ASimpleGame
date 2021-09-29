#pragma once
#include "playerclass.h"
class C_PASSIVE
{
public:
	typedef void (C_PASSIVE::* FP_P)(float, C_UNIT&, C_UNIT&, float&);
	/*enum E_AFFECT
	{
		Lifesteal,
		MagicBasicRate,
		HealthCostReduction,
		ManaCostReduction,
		DamageReflection,
		DamageAmplification,
		DamageReduction,
		HealAmplification,
		ApplyState,
		AffectMax
	};*/
	enum E_CONDITION
	{
		BasicAttack,
		TakeDamage,
		HealthCost,
		ManaCost,
		SkillAmount,
		TurnBegin,
		TurnEnd,
		ConditionMax
	};

private:
	std::string szName;
	std::string szExplained;
	std::pair<FP_P, float>* pairPassive[ConditionMax];

public:
	C_PASSIVE();
	void setPassive(const std::string& _name, const std::string& _detail, std::pair<FP_P, float>** _pair);
	bool callPassive(E_CONDITION _cd, C_UNIT& _caster, C_UNIT& _target, float& _number);
	void reflectDamage(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _damage);
	void release();
	void lifesteal(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _damage);
	void magicBasic(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _damage);
	void reduceHealthCost(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _cost);
	void reduceManaCost(float _rate, C_UNIT& _caster, C_UNIT& _target, float& _cost);
};

