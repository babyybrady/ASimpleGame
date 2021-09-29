#pragma once
#include "stat.h"
#include <string>

class C_UNIT;

class C_SKILL
{
public:
	enum class E_TARGET
	{
		Ally,
		Foe
	};
	enum class E_AFFECTTYPE
	{
		BasicAttack,
		Damage,
		Heal,
		ManaRestoration,
		ApplyState,
		Lifesteal,
		DamageReflection,
		AffectMax
	};
private:
	class C_SKILL* pNext;
	C_STAT cScale;
	std::string szName;
	std::string szExplained;
	float fHealthCost;
	float fManaCost;
	int nRequiredLevel;
	E_TARGET eSkillTarget;
	E_AFFECTTYPE eSkillType;

public:
	C_SKILL();
	virtual ~C_SKILL();
	void setSkill(const std::string& _name, const std::string& _detail, const std::vector<float>& _stats, 
		int _lvl, float _hc, float _mc, E_TARGET _target, E_AFFECTTYPE _type, C_SKILL* _pNext = nullptr);
	C_STAT& getScale();
	float getHealthCost();
	float getManaCost();
	int getRequiredLevel();
	const std::string& getName();
	const std::string& getDetail();
	E_TARGET getTarget();
	bool hasEnoughCost(C_UNIT& _caster, float _hc, float _mc);
	bool isTargetValid(C_UNIT& _caster, C_UNIT& _target);
	float skillAmount(C_UNIT& _caster, C_UNIT& _target);
	void useSkill(C_UNIT& _caster, C_UNIT& _target);
	bool hasNext();
	virtual void doAffect(C_UNIT& _caster, C_UNIT& _target, float _amount = 0);
	void doBasicAttack(C_UNIT& _attacker, C_UNIT& _defender, float _amount);
	void doDamage(C_UNIT& _attacker, C_UNIT& _defender, float _amount);
	void doHeal(C_UNIT& _healer, C_UNIT& _target, float _amount);
	void doManaRestoration(C_UNIT& _restorer, C_UNIT& _target, float _amount);
};