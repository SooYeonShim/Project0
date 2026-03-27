#pragma once
#include <iostream>
#include "Player.h"

using namespace std;

class ShopManager
{
public:
    static ShopManager& getInstance()
    {
        static ShopManager instance; // 최초 1회만 생성
        return instance;
    }

    void HealAllPlayer(vector<Player>& Players, int& PlayerMoney);
    void BuyItem(int& PlayerMoney);
    void EnterShop(vector<Player>& Players, int& PlayerMoney);
    int GetUserInputNum();
    void PrintShopUI(int PlayerMoney);

private:
    // 생성자를 private으로 막음
    ShopManager() {}

    // 복사/대입도 막음
    ShopManager(const ShopManager&) = delete;
    ShopManager& operator=(const ShopManager&) = delete;
    
};

