#include <algorithm>
#include "InventoryManager.h"


    bool InventoryManager::AddItem(Item* Item) {
        if (ItemList.size() >= MaxCapacity) {
            std::cout << "인벤토리가 가득 찼습니다.\n";
            delete Item;
            return false;
        }
        ItemList.push_back(Item);
        return true;
    }

    bool InventoryManager::IsValidIndex(int index) {
        if (index < 0 || index >= ItemList.size()) {
            return false; // 범위 밖이면 바로 false
        }
        return ItemList[index] != nullptr;
    }

    bool InventoryManager::Use(int index, Character* target) {
        if (index < 0 || index >= ItemList.size())
            return false;
        std::cout << ItemList[index]->GetName() << " 사용!\n";
        if (ItemList[index]->Use(*target))
        {
            delete ItemList[index];
            ItemList.erase(ItemList.begin() + index);
            return true;
        }
        else
        {
            return false;
        }
    }

    void InventoryManager::ShowInventory() {
        std::cout << "현재 인벤토리:\n";
        if (ItemList.empty()) {
            std::cout << "아이템이 없습니다.\n";
            return;
        }
        for (int i = 0; i < ItemList.size(); i++) {
            std::cout << "[" << i+1 << "] " << ItemList[i]->GetName() << " : " << ItemList[i]->GetItemInfo() << ")\n";
        }
    }

