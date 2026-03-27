#pragma once

#include <map>
#include <string>
#include "Player.h"
#include "Dice.h"

#include "Goblin.h"
#include "Orc.h"
#include "Wolf.h"
#include "HealingPotion.h"

using namespace std;

class TemplateManager
{
private:


public:
    static TemplateManager& getInstance()
    {
        static TemplateManager instance; // 최초 1회만 생성
        return instance;
    }

public:
    // 초기 생성, 몬스터
    Goblin GetMonsterByGoblin();
    Orc GetMonsterByOrc();
    Wolf GetMonsterByWolf();

    Dice GetDiceByGobline();
    Dice GetDiceByOrc();
    Dice GetDiceByWolf();

    // 직업 주사위
    Dice GetDiceByWarrior();
    Dice GetDiceByArcher();
    Dice GetDiceByDefender();
    Dice GetDiceByRogue();

    // 직업타입을 주면 직업주사위반환
    Dice GetDiceByType(JobType _type);

    // 직업 타입을 주면 직업 반환
    Player GetPlayerByType(string Nickname, JobType _type);

    // 아이템 생성
    //*주의! 해당 포인터는 힙메모리에 있고 명확한 소유주가 없기에 메모리관리를 주의해야함*
    Item* GetHealingPotion();

private:
    // 생성자를 private으로 막음
    TemplateManager() {}

    // 복사/대입도 막음
    TemplateManager(const TemplateManager&) = delete;
    TemplateManager& operator=(const TemplateManager&) = delete;
};

