#pragma once
#include <map>
#include <string>
#include "passive.h"

class C_PASSIVEMGR
{
private:
	static std::map<std::string, C_PASSIVE*> mapPassive;

public:
	C_PASSIVEMGR() = delete;
	static void loadData();
	static void clearData();
	static C_PASSIVE* findPassive(const std::string& _name);
};

