#pragma once
#include <iostream>
#include "Player.h"
#include "InventoryManager.h"
#include "HealingPotion.h"
#include "Item.h"
#include "UIManager.h"

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
    void PrintShopUI(int PlayerMoney);

    // Action 구입 창
    void ShopActionUI(vector<Player>& Players, int& PlayerMoney);

private:
    // 생성자를 private으로 막음
    ShopManager() {}

    // 복사/대입도 막음
    ShopManager(const ShopManager&) = delete;
    ShopManager& operator=(const ShopManager&) = delete;
    
};

