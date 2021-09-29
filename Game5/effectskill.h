#pragma once
#include "skill.h"
#include "statuseffect.h"
#include "unit.h"

class C_EFFECT_SKILL : public C_SKILL
{
private:
	C_STATUS_EFFECT* pStatusEffect;

private:
	C_UNIT::S_NODE* createNode();

public:
	C_EFFECT_SKILL();
	void setEffectSkill(C_STATUS_EFFECT* _effect, const char* _name, const char* _detail, const std::vector<float>& _stats, int _lvl, float _hp, float _mp, E_TARGET _target, C_SKILL* _pNext = nullptr);
	const C_STATUS_EFFECT* getStatusEffect();
	void doApplyStatusEffect(C_UNIT& _caster, C_UNIT& _target);
	virtual void doAffect(C_UNIT& _caster, C_UNIT& _target, float _amount = 0) override;
};