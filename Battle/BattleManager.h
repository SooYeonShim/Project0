#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <map>

#include "Player.h"
#include "MonsterSpawn.h"
#include "Monster.h"
#include "GameEnums.h"
#include "UIManager.h"
#include "InventoryManager.h"

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

    void RollDiceByPlayers(vector<Player>& players);


    BattleManager();
    // 복사/대입도 막음
    BattleManager(const BattleManager&) = delete;
    BattleManager& operator=(const BattleManager&) = delete;

    int RerollCount;    
};
