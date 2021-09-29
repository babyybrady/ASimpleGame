#pragma once
#include "stat.h"
#include <string>
#include <list>

struct S_NODE;
class C_SKILL;
class C_STATUS_EFFECT;
class C_UNIT_CLASS;

class C_UNIT
{
public:
	struct S_NODE
	{
		C_STATUS_EFFECT* pStatusEffect;
		int nTurnRemaining;
	};
	enum class E_FORCE
	{
		Neutral,
		Friendly,
		Enemy
	};
	enum { SlotsMax = 10 };

protected:
	std::string szName;
	C_STAT cUnitStats;
	C_STAT cEffectStats;
	E_FORCE unitForce;
	C_UNIT_CLASS* pClass;

public:
	std::list<S_NODE*> listStatusEffect;
	C_SKILL* pUnitSkills[SlotsMax];

public:
	C_UNIT();
	void setUnit(const std::string& _name, const std::vector<float>& _stats, E_FORCE _fc, C_UNIT_CLASS* _class);
	C_STAT& getUnitStats();
	C_STAT& getEffectStats();
	C_UNIT_CLASS* getClass();
	const std::string& getName();
	E_FORCE getForce();
	void changeClass(C_UNIT_CLASS* _class);
	void changeHealth(float _health);
	void changeMana(float _mana);
	virtual bool forgetSkill(size_t _slot);
	virtual bool learnSkill(C_SKILL* _skill, size_t _slot);
	void recoverHP();
	void recoverMP();
	void resetHP();
	void resetMP();
	void restoreResources();
	void resetResources();
	void initiateStatusEffects();
	void terminateStatusEffects();
	void printStatusEffects();
	void printUnit();
	void printSkills();
	void useSkillBySlot(int _slot, C_UNIT& _target);

};

int inputInt(int _min, int _max);