#include "statuseffectmgr.h"
#include "statuseffect.h"

std::map<std::string, C_STATUS_EFFECT*> C_STATUSEFFECTMGR::mapStatusEffect{};

void C_STATUSEFFECTMGR::loadData()
{
	std::vector<float> vStats{};
	vStats.reserve(C_STAT::E_STAT::StatsMax);
	C_STATUS_EFFECT* pGuarding = new C_STATUS_EFFECT{};
	vStats = { 0, 0, 0, 1, 0, 1, 0, 0.2f };
	pGuarding->setStatusEffect(1, "Guarding", vStats);
	mapStatusEffect.insert(std::pair<std::string, C_STATUS_EFFECT*>("Guarding", pGuarding));
	C_STATUS_EFFECT* pReinforced = new C_STATUS_EFFECT{};
	vStats = { 0, 0, 0.5f, 0, 0.5f, 0, 0, 0 };
	pReinforced->setStatusEffect(3, "Reinforced", vStats, true);
	mapStatusEffect.insert(std::pair<std::string, C_STATUS_EFFECT*>("Reinforced", pReinforced));
}

void C_STATUSEFFECTMGR::clearData()
{
	for (std::pair<std::string, C_STATUS_EFFECT*> pair : mapStatusEffect)
	{
		C_STATUS_EFFECT* pStatusEffect = pair.second;
		delete pStatusEffect;
	}
	mapStatusEffect.clear();
}

C_STATUS_EFFECT* C_STATUSEFFECTMGR::findStatusEffect(const std::string& _name)
{
	std::map<std::string, C_STATUS_EFFECT*>::iterator iter = mapStatusEffect.find(_name);
	if (iter == mapStatusEffect.end())
		return nullptr;
	return iter->second;
}
