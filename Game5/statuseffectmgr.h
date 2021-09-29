#pragma once
#include <map>
#include <string>
class C_STATUS_EFFECT;

class C_STATUSEFFECTMGR
{
private:
	static std::map<std::string, C_STATUS_EFFECT*> mapStatusEffect;

public:
	C_STATUSEFFECTMGR() = delete;
	static void loadData();
	static void clearData();
	static C_STATUS_EFFECT* findStatusEffect(const std::string& _name);
};

