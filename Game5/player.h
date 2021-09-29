#pragma once
#include "unit.h"
class C_SKILL;
class C_MONSTER;
class C_PLAYER_CLASS;

class C_PLAYER : public C_UNIT
{
private:
	int nLevel;
	float fExp;
	float fRequiredExp;

public:
	C_PLAYER();
	void setPlayer(std::string& _name, E_FORCE _fc, C_PLAYER_CLASS* _class, int _level = 1, float _exp = 0);
	int getLevel();
	void changeClass(C_PLAYER_CLASS* _class);
	virtual bool forgetSkill(size_t _slot);
	virtual bool learnSkill(C_SKILL* _skill, size_t _slot);
	void printPlayer();
	void killedMonster(C_MONSTER& _monster);
	void levelUp();
};

void enter();