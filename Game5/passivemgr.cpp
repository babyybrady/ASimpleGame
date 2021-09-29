#include "passivemgr.h"
#include "passive.h"
#include "skillmgr.h"
#include "statuseffectmgr.h"
#include "effectskill.h"

std::map<std::string, C_PASSIVE*> C_PASSIVEMGR::mapPassive{};

void C_PASSIVEMGR::loadData()
{
	std::pair<C_PASSIVE::FP_P, float>* pairPassive[C_PASSIVE::E_CONDITION::ConditionMax]{};

	C_PASSIVE* pBeginnerPassive = new C_PASSIVE{};
	pBeginnerPassive->setPassive("NoPassive", "�ƹ��� ����� ���� �нú��̴�.", pairPassive);
	mapPassive.insert(std::pair<std::string, C_PASSIVE*>("NoPassive", pBeginnerPassive));

	pairPassive[C_PASSIVE::E_CONDITION::BasicAttack] = new std::pair<C_PASSIVE::FP_P, float>(&C_PASSIVE::lifesteal, 0.2f);
	pairPassive[C_PASSIVE::E_CONDITION::TakeDamage] = new std::pair<C_PASSIVE::FP_P, float>(&C_PASSIVE::reflectDamage, 0.2f);
	C_PASSIVE* pWarriorPassive = new C_PASSIVE{};
	pWarriorPassive->setPassive("CombatMaster", "�⺻ ���� �� ���ط��� 20%�� �ش��ϴ� ü���� ȸ��, ���� ���ط��� 20%��ŭ�� ��뿡�� �ݰ�.", pairPassive);
	mapPassive.insert(std::pair<std::string, C_PASSIVE*>("CombatMaster", pWarriorPassive));

	pairPassive[C_PASSIVE::E_CONDITION::TakeDamage] = nullptr;

	pairPassive[C_PASSIVE::E_CONDITION::BasicAttack] = new std::pair<C_PASSIVE::FP_P, float>(&C_PASSIVE::magicBasic, 1.f);
	pairPassive[C_PASSIVE::E_CONDITION::ManaCost] = new std::pair<C_PASSIVE::FP_P, float>(&C_PASSIVE::reduceManaCost, 0.25f);
	C_PASSIVE* pMagicianPassive = new C_PASSIVE{};
	pMagicianPassive->setPassive("MagicMaster", "�⺻ ���� �� �������ݷ��� 100%�� ���� ���ط� ����. ���� ��ų ���� ���� �Ҹ� 25% ����.", pairPassive);
	mapPassive.insert(std::pair<std::string, C_PASSIVE*>("MagicMaster", pMagicianPassive));

	pairPassive[C_PASSIVE::E_CONDITION::BasicAttack] = nullptr;
	pairPassive[C_PASSIVE::E_CONDITION::ManaCost] = nullptr;
}

void C_PASSIVEMGR::clearData()
{
	for (std::pair<std::string, C_PASSIVE*> pair : mapPassive)
	{
		C_PASSIVE* pPassive = pair.second;
		pPassive->release();
		delete pPassive;
	}
	mapPassive.clear();
}

C_PASSIVE* C_PASSIVEMGR::findPassive(const std::string& _name)
{
	std::map<std::string, C_PASSIVE*>::iterator iter = mapPassive.find(_name);
	if (iter == mapPassive.end())
		return nullptr;
	return iter->second;
}
