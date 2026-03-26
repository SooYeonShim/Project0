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
    // 초기 생성
    Goblin GetMonsterByGoblin();
    Orc GetMonsterByOrc();
    Wolf GetMonsterByWolf();

    Dice GetDiceByGobline();
    Dice GetDiceByOrc();
    Dice GetDiceByWolf();


private:
    // 생성자를 private으로 막음
    TemplateManager() {}

    // 복사/대입도 막음
    TemplateManager(const TemplateManager&) = delete;
    TemplateManager& operator=(const TemplateManager&) = delete;
};

