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
	pBasicAttack->setSkill("BasicAttack", "���� ����. ���ݷ��� 100%�� �����Ѵ�.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::BasicAttack);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("BasicAttack", pBasicAttack));
	
	C_SKILL* pLifesteal = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pLifesteal->setSkill("Lifesteal", "������ ���� ���ط��� �Ϻθ� ȸ���Ѵ�.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Ally, C_SKILL::E_AFFECTTYPE::Heal);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Lifesteal", pLifesteal));

	C_SKILL* pBasicMagic = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 1, -1, 0, 0 };
	pBasicMagic->setSkill("BasicMagic", "���� ����. �������ݷ��� 100%�� �����Ѵ�. �⺻������ ��ü�ϴ� ����.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("BasicMagic", pBasicMagic));
	
	C_SKILL* pReflectDamage = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pReflectDamage->setSkill("ReflectDamage", "������ ���� ���ط��� �Ϻθ� �����ش�.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("ReflectDamage", pReflectDamage));

	C_EFFECT_SKILL* pDefend = new C_EFFECT_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pDefend->setEffectSkill(C_STATUSEFFECTMGR::findStatusEffect("Guarding"), "Defend", "��� ���. 1�ϰ� �ڽ��� ���°� ���������� 2�� ��½�Ű�� �� ����� ������ 20% ȸ���Ѵ�.", vStats, 0, 0, 0, C_SKILL::E_TARGET::Ally);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Defend", pDefend));

	C_SKILL* pFireBall = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 2.5f, -1.75f, 0, 0 };
	pFireBall->setSkill("FireBall", "���� ����. ���� 3�� �Ҹ��Ͽ� ȭ������ ����� �������׷��� 30% �����ϸ� �������ݷ��� 250%�� �����Ѵ�.", vStats, 2, 0, 3, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("FireBall", pFireBall));

	C_SKILL* pSelfHeal = new C_SKILL{};
	vStats = { 0, 0, 0, 0, 5, 0, 0, 0 };
	pSelfHeal->setSkill("SelfHeal", "ü�� ȸ�� ���. ���� 5�� �Ҹ��Ͽ� �ڽ��� ü���� �ִ� �������ݷ��� 500%��ŭ ȸ���Ѵ�.", vStats, 3, 0, 5, C_SKILL::E_TARGET::Ally, C_SKILL::E_AFFECTTYPE::Heal);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("SelfHeal", pSelfHeal));
	
	C_EFFECT_SKILL* pReinforcement = new C_EFFECT_SKILL{};
	vStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
	pReinforcement->setEffectSkill(C_STATUSEFFECTMGR::findStatusEffect("Reinforced"), "Reinforcement", "��ȭ ���. ������ 2 �Ҹ��Ͽ� 3�ϰ� �ڽ��� ���ݷ°� �������ݷ��� 50% ��½�Ų��. ��ø ����.", vStats, 4, 0, 2, C_SKILL::E_TARGET::Ally);
	mapSkill.insert(std::pair<std::string, C_SKILL*>("Reinforcement", pReinforcement));

	C_SKILL* pTripleAttack = new C_SKILL[3]{};
	vStats = { 0, 0, 1, -1, 0, 0, 0, 0 };
	pTripleAttack[0].setSkill("TripleAttack", "���� ����. ü���� 10 �Һ��Ͽ� ���ݷ��� 100%, 150%, 300%�� �� �� �� �����Ѵ�. ������ ������ ������ �����Ѵ�.", vStats, 5, -10, 0, C_SKILL::E_TARGET::Foe, C_SKILL::E_AFFECTTYPE::Damage, pTripleAttack + 1);
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
