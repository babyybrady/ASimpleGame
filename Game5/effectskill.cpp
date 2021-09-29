#include "effectskill.h"
#include <iostream>

C_UNIT::S_NODE* C_EFFECT_SKILL::createNode()
{
	C_UNIT::S_NODE* pNewNode{};

	pNewNode = new C_UNIT::S_NODE{};
	pNewNode->pStatusEffect = pStatusEffect;
	pNewNode->nTurnRemaining = pStatusEffect->getTurns();

	return pNewNode;
}

C_EFFECT_SKILL::C_EFFECT_SKILL() : C_SKILL(), pStatusEffect{}
{
}

void C_EFFECT_SKILL::setEffectSkill(C_STATUS_EFFECT* _effect, const char* _name, const char* _detail, const std::vector<float>& _stats, int _lvl, float _hp, float _mp, E_TARGET _target, C_SKILL* _next)
{
	setSkill(_name, _detail, _stats, _lvl, _hp, _mp, _target, C_SKILL::E_AFFECTTYPE::ApplyState, _next);
	pStatusEffect = _effect;
}
const C_STATUS_EFFECT* C_EFFECT_SKILL::getStatusEffect()
{
	return pStatusEffect;
}
void C_EFFECT_SKILL::doApplyStatusEffect(C_UNIT& _caster, C_UNIT& _target)
{
	if (pStatusEffect->isStackable())
	{
		_target.listStatusEffect.push_back(createNode());
		std::cout << _caster.getName() << "(이)가 " << _target.getName() << "에게 상태 " << pStatusEffect->getName() << "를 " << pStatusEffect->getTurns() << "턴간 부여해 주었습니다." << std::endl;
		_target.initiateStatusEffects();
		_target.printStatusEffects();
		return;
	}
	std::list<C_UNIT::S_NODE*>::iterator iter = _target.listStatusEffect.begin();
	while (iter != _target.listStatusEffect.end() && (*iter)->pStatusEffect != pStatusEffect)
		iter++;
	
	if (iter != _target.listStatusEffect.end())
	{
		std::cout << "이미 적용중인 중첩불가 상태입니다. 지속턴이 갱신됩니다." << std::endl;
		_target.printStatusEffects();
		return; 
	}
	_target.listStatusEffect.push_back(createNode());
	std::cout << _caster.getName() << "(이)가 " << _target.getName() << "에게 상태 " << pStatusEffect->getName() << "를 " << pStatusEffect->getTurns() << "턴간 부여해 주었습니다." << std::endl;
	_target.initiateStatusEffects();
	_target.printStatusEffects();
}

void C_EFFECT_SKILL::doAffect(C_UNIT& _caster, C_UNIT& _target, float _amount)
{
	doApplyStatusEffect(_caster, _target);
}
