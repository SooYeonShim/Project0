#pragma once
#include <iostream>
#include <vector>
#include "Player.h"

class BattleManager
{
public:
    static BattleManager& getInstance() 
    {
        static BattleManager instance; // 최초 1회만 생성
        return instance;

        bool Battle(vector<Player>&, int Stage);
        void AddRerollCount();
    }

private:
    // 생성자를 private으로 막음
    BattleManager() {}

    // 복사/대입도 막음
    BattleManager(const BattleManager&) = delete;
    BattleManager& operator=(const BattleManager&) = delete;

    int RerollCount;
   

};
