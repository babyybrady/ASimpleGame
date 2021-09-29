#include "effectskill.h"
#include "player.h"
#include "monster.h"
#include "statuseffectmgr.h"
#include "skillmgr.h"
#include "playerclassmgr.h"
#include "passivemgr.h"
#include <iostream>

int inputInt(int _min, int _max);
void enter();

int main()
{
	C_STATUSEFFECTMGR::loadData();
	C_SKILLMGR::loadData();
	C_PASSIVEMGR::loadData();
	C_PLAYERCLASSMGR::loadData();

	std::string szPlayerName{};
	std::vector<float> vStats{};
	std::vector<float> vGrowthStats{};

	std::cout << "플레이 할 캐릭터의 이름을 입력하세요: ";
	std::cin >> szPlayerName;

	C_PLAYER Player1{};
	Player1.setPlayer(szPlayerName, C_UNIT::E_FORCE::Friendly, C_PLAYERCLASSMGR::findPlayerClass("Beginner"));
	Player1.learnSkill(C_SKILLMGR::findSkill("Debugger"), 0);

	std::string szMonsterName{};

	std::cout << "상대할 캐릭터의 이름을 입력하세요: ";
	std::cin >> szMonsterName;

	C_MONSTER Monster1{};
	vStats = { 50, 5, 3, 0, 1, 0, 0, 0 };
	vGrowthStats = { 10, 2, 2, 1, 1, 1, 0, 0 };
	Monster1.setMonster(szMonsterName, vStats, vGrowthStats, C_UNIT::E_FORCE::Enemy, nullptr);

	while (Player1.getUnitStats().getStat(C_STAT::E_STAT::CurrentHealth) > 0)
	{
		Player1.initiateStatusEffects();
		Monster1.initiateStatusEffects();
		int nInput{};
		system("cls");
		Player1.printPlayer();
		std::cout << "==================================================" << std::endl;
		Monster1.printUnit();
		std::cout << "==================================================" << std::endl;
		std::cout << "1. 공격 2. 방어 3. 스킬 사용 4. 종료" << std::endl;
		std::cout << "나의 행동>> ";
		nInput = inputInt(1, 4);
		std::cout << "==================================================" << std::endl;
		switch (nInput)
		{
		case 1:
			std::cout << "적에게 공격을 가해 피해를 입힙니다." << std::endl;
			C_SKILLMGR::findSkill("BasicAttack")->useSkill(Player1, Monster1);
			break;
		case 2:
			std::cout << "방어태세에 돌입하여 자신의 방어력, 마법저항력을 2배 높이고 턴 종료시 마나를 20% 회복합니다." << std::endl;
			C_SKILLMGR::findSkill("Defend")->doAffect(Player1, Player1);
			break;
		case 3:
		{
			std::cout << "스킬 목록" << std::endl;
			Player1.printSkills();
			std::cout << "==================================================" << std::endl;

			int nSlot{};
			std::cout << "사용할 스킬의 슬롯번호를 입력해 주세요[0 ~ 9] >> ";
			nSlot = inputInt(0, 9);
			C_SKILL::E_TARGET tgt{};
			std::cout << "스킬을 사용할 대상을 입력해 주세요(자기자신: 0, 적: 1) >> ";
			tgt = static_cast<C_SKILL::E_TARGET>(inputInt(0, 1));
			if (tgt == C_SKILL::E_TARGET::Foe)
				Player1.useSkillBySlot(nSlot, Monster1);
			else if (tgt == C_SKILL::E_TARGET::Ally)
				Player1.useSkillBySlot(nSlot, Player1);
			break;
		}
		case 4:
			std::cout << "엔터키를 입력하면 종료합니다." << std::endl;
			std::cout << "==================================================" << std::endl;
			enter();

			C_STATUSEFFECTMGR::clearData();
			C_SKILLMGR::clearData();
			C_PASSIVEMGR::clearData();
			C_PLAYERCLASSMGR::clearData();
			return 0;
		}
		std::cout << "==================================================" << std::endl;
		Monster1.printStatusEffects();
		Monster1.initiateStatusEffects();
		std::cout << "적의 공격을 받아 피해를 입습니다." << std::endl;
		C_SKILLMGR::findSkill("BasicAttack")->useSkill(Monster1, Player1);
		std::cout << "==================================================" << std::endl;

		if (Monster1.getUnitStats().getStat(C_STAT::E_STAT::CurrentHealth) <= 0)
		{
			Player1.killedMonster(Monster1);
			Monster1.spawnMonster(szMonsterName, nullptr);
		}
		Player1.terminateStatusEffects();
		Monster1.terminateStatusEffects();
		std::cout << "엔터키를 눌러 진행하세요." << std::endl;
		std::cout << "==================================================" << std::endl;
		enter();
	}
	std::cout << "사망하셨습니다." << std::endl << "엔터키를 입력하면 종료합니다." << std::endl;
	std::cout << "==================================================" << std::endl;
	enter();

	C_STATUSEFFECTMGR::clearData();
	C_SKILLMGR::clearData();
	C_PASSIVEMGR::clearData();
	C_PLAYERCLASSMGR::clearData();
	return 0;
}

int inputInt(int _min, int _max)
{
	int nInput{};
	do
	{
		std::cin >> nInput;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (!std::cin || nInput < _min || nInput > _max);
	return nInput;
}
void enter()
{
	//getchar();
	//while (fgetc(stdin) != '\n');
	std::cin.clear();
	//std::cin.ignore();
	std::string sz{};
	std::getline(std::cin, sz);
}