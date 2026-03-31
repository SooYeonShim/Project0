#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "BattleManager.h"
#include "../Shop/ShopManager.h"
#include "Character.h"
#include "InventoryManager.h"
#include "Dice.h"
#include "HealingPotion.h"
#include "Item.h"
#include "../Template/TemplateManager.h"
#include "UIManager.h"


using namespace std;

class GameManager
{
public:
    static GameManager& getInstance()
    {
        static GameManager instance; // 최초 1회만 생성
        return instance;
    }



    void InitializeCharacter(vector<Player>& Players);
    // true : 엔딩 false : 게임오버
    bool GameStart();
    bool BattleResult(bool Result);
    void PrintPlayerDice();
    string GetJobName(JobType JobType);


private:
    // 생성자를 private으로 막음
    GameManager()
    {
        PlayerMoney = 0;
    }

    // 복사/대입도 막음
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    int CurrentStage;
    bool GameResult;
    int PlayerMoney;
    int DeathCount = 0;
    vector<Player> Players;


};
