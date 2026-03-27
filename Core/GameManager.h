#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "BattleManager.h"
#include "../Shop/ShopManager.h"
#include "Character.h"
#include "Dice.h"
#include "../Template/TemplateManager.h"


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
    void GameStart();
    bool BattleResult(bool Result);
    void PrintPlayerDice(vector<Player>& Players);
    int GetUserInputNum();
    int GetPlayerByName();


private:
    // 생성자를 private으로 막음
    GameManager() {}

    // 복사/대입도 막음
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    int CurrentStage;
    bool GameResult;
    int PlayerMoney = 100;

    vector<Player> Players;


};
