#pragma once
#include <iostream>
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "Goblin.h"

class BattleManager
{
public:
    static BattleManager& getInstance()
    {
        static BattleManager instance; // 최초 1회만 생성
        return instance;
    }

    bool Battle(vector<Player>&, int Stage);
    void AddRerollCount(int count);    

private:

    BattleManager();
    // 복사/대입도 막음
    BattleManager(const BattleManager&) = delete;
    BattleManager& operator=(const BattleManager&) = delete;

    int RerollCount;
   

};
