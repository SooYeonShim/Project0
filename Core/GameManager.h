#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "BattleManager.h"
#include "Character.h"
#include "Dice.h"

using namespace std;

class GameManager
{
public:
    static GameManager& getInstance() {
        static GameManager instance; // 최초 1회만 생성
        return instance;
    }



    void InitializeCharacter(vector<Player>& Players);
    void GameStart();
    void BattleResult(bool Result);

private:
    // 생성자를 private으로 막음
    GameManager() {}

    // 복사/대입도 막음
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    int CurrentStage;
    vector<Player> Players;


};
