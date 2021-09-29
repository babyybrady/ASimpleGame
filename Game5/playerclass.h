#pragma once
#include "unitclass.h"
#include <map>
class C_PLAYER;
class C_PASSIVE;

class C_PLAYER_CLASS : public C_UNIT_CLASS
{
private:
	C_STAT cGrowth;
	std::map<int, C_SKILL*> mapClassSkill;
	std::map<int, C_PLAYER_CLASS*> mapSubclass;

public:
	C_PLAYER_CLASS();
	void setPlayerClass
	(const std::string& _name, const std::vector<float>& _bs, C_PASSIVE* _passive, const std::vector<float>& _gs,
		const std::map<int, C_SKILL*> _cs, const std::map<int, C_PLAYER_CLASS*> _sc);
	void changeSubclass(C_PLAYER& _player);
	void growUp(C_UNIT* _unit) override;
	void learnClassSkill(C_PLAYER& _player);
	void levelUp(C_PLAYER& _player);
	C_STAT& getGrowthStats() override;
};
