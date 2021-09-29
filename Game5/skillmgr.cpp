#include "skillmgr.h"
#include "statuseffectmgr.h"
#include "effectskill.h"

std::map<std::string, C_SKILL*> C_SKILLMGR::mapSkill{};
void (C_SKILL::* (C_SKILLMGR::fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::AffectMax)]))(C_UNIT&, C_UNIT&, float) {};

void C_SKILLMGR::loadData()
{
	std::vector<float> vStats{};
	vStats.reserve(C_STAT::E_STAT::StatsMax);

	C_SKILL* pBasicAttack = new C_SKILL{};
	vStats = { 0, 0, 1, -1, 0, 0, 0, 0 };
	pBasicAttack->setSkill("BasicAttack", "물리 공격. 공격력의 100%로 공격한다.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::BasicAttack);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("BasicAttack", pBasicAttack));
	
	C_SKILL* pLifesteal = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pLifesteal->setSkill("Lifesteal", "적에게 가한 피해량의 일부를 회복한다.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Ally, C_SKILL::E_AFFECTTYPE::Heal);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Lifesteal", pLifesteal));

	C_SKILL* pBasicMagic = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 1, -1, 0, 0 };
	pBasicMagic->setSkill("BasicMagic", "마법 공격. 마법공격력의 100%로 공격한다. 기본공격을 대체하는 마법.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("BasicMagic", pBasicMagic));
	
	C_SKILL* pReflectDamage = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pReflectDamage->setSkill("ReflectDamage", "적에게 받은 피해량의 일부를 돌려준다.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("ReflectDamage", pReflectDamage));

	C_EFFECT_SKILL* pDefend = new C_EFFECT_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pDefend->setEffectSkill(C_STATUSEFFECTMGR::findStatusEffect("Guarding"), "Defend", "방어 기술. 1턴간 자신의 방어력과 마법방어력을 2배 상승시키고 턴 종료시 마나를 20% 회복한다.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Ally);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Defend", pDefend));

	C_SKILL* pFireBall = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 2.5f, -1.75f, 0, 0 };
	pFireBall->setSkill("FireBall", "마법 공격. 마력 3을 소모하여 화염구를 만들어 마법저항력을 30% 관통하며 마법공격력의 250%로 공격한다.", vStats, 2, 0, 3, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("FireBall", pFireBall));

	C_SKILL* pSelfHeal = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 5, 0, 0, 0 };
	pSelfHeal->setSkill("SelfHeal", "체력 회복 기술. 마력 5를 소모하여 자신의 체력을 최대 마법공격력의 500%만큼 회복한다.", vStats, 3, 0, 5, C_SKILL::E_TARGET::Ally, C_SKILL::E_AFFECTTYPE::Heal);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("SelfHeal", pSelfHeal));
	
	C_EFFECT_SKILL* pReinforcement = new C_EFFECT_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pReinforcement->setEffectSkill(C_STATUSEFFECTMGR::findStatusEffect("Reinforced"), "Reinforcement", "강화 기술. 마력을 2 소모하여 3턴간 자신의 공격력과 마법공격력을 50% 상승시킨다. 중첩 가능.", vStats, 4, 0, 2, C_SKILL::E_TARGET::Ally);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Reinforcement", pReinforcement));

	C_SKILL* pTripleAttack = new C_SKILL[3]{};
	vStats = { 0, 0, 1, -1, 0, 0, 0, 0 };
	pTripleAttack[0].setSkill("TripleAttack", "물리 공격. 체력을 10 소비하여 공격력의 100%, 150%, 300%로 총 세 번 공격한다. 마지막 공격은 방어력을 무시한다.", vStats, 5, -10, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage, pTripleAttack + 1);
	vStats = { 0, 0, 1.5f, -1.5f, 0, 0, 0, 0 };
	pTripleAttack[1].setSkill("TripleAttack", "", vStats, 5, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage, pTripleAttack + 2);
	vStats = { 0, 0, 3, 0, 0, 0, 0, 0 };
	pTripleAttack[2].setSkill("TripleAttack", "", vStats, 5, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("TripleAttack", pTripleAttack));

	C_SKILL* pDebugger = new C_SKILL{};
	vStats = { 1, 0, 0, 0, 0, 0, 0, 0 };
	pDebugger->setSkill("Debugger", "", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Debugger", pDebugger));

	fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::BasicAttack)] = &C_SKILL::doBasicAttack;
	fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::Damage)] = &C_SKILL::doDamage;
	fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::Heal)] = &C_SKILL::doHeal;
	fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::ManaRestoration)] = &C_SKILL::doManaRestoration;
	fpAffect[static_cast<int>(C_SKILL::E_AFFECTTYPE::ApplyState)] = nullptr;
}

void C_SKILLMGR::clearData()
{
	for (std::pair<std::string, C_SKILL*> pair : mapSkill)
	{
		C_SKILL* pSkill = pair.second;
		if (pSkill->hasNext())
			delete[] pSkill;
		else delete pSkill;
	}
	mapSkill.clear();
}

C_SKILL* C_SKILLMGR::findSkill(const std::string& _name)
{
	std::map<std::string, C_SKILL*>::iterator iter = mapSkill.find(_name);
	if (iter == mapSkill.end())
		return nullptr;
	return iter->second;
}
