#pragma once
#include <map>
#include <string>
#include "playerclass.h"

class C_PLAYERCLASSMGR
{
private:
	static std::map<std::string, C_PLAYER_CLASS*> mapPlayerClass;

public:
	C_PLAYERCLASSMGR() = delete;
	static void loadData();
	static void clearData();
	static C_PLAYER_CLASS* findPlayerClass(const std::string& _name);
};

