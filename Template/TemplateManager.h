#pragma once

#include <map>
#include <string>
#include "Player.h"
#include "Dice.h"

#include "Goblin.h"
#include "Orc.h"
#include "Wolf.h"

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

    // 주사위면 입력수치만큼을 새롭게 만들어서 보내줌

private:
    // 생성자를 private으로 막음
    TemplateManager() {}

    // 복사/대입도 막음
    TemplateManager(const TemplateManager&) = delete;
    TemplateManager& operator=(const TemplateManager&) = delete;
};

