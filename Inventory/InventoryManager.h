#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"

using namespace std;

class InventoryManager
{
public:
    static InventoryManager& getInstance() {
        static InventoryManager instance;
        return instance;
    }

    bool AddItem(Item* Item);
    bool IsValidIndex(int index);
    bool Use(int index, Character* target);
    void ShowInventory();

private:
    // 생성자 막기
    InventoryManager() : MaxCapacity(3) {}

    // 복사/대입 막기
    InventoryManager(const InventoryManager&) = delete;
    InventoryManager& operator=(const InventoryManager&) = delete;

    vector<Item*> ItemList;
    int MaxCapacity;
    

};
