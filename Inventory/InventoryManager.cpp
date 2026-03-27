#include <algorithm>
#include "InventoryManager.h"


    Item* InventoryManager::AddItem(Item* Item) {
        if (ItemList.size() >= MaxCapacity) {
            std::cout << "인벤토리가 가득 찼습니다.\n";
            return nullptr;
        }
        ItemList.push_back(Item);
        return ItemList.back();
    }

    bool InventoryManager::Use(int index, Character* target) {
        if (index < 0 || index >= ItemList.size())
            return false;
        std::cout << ItemList[index]->GetName() << " 사용!\n";
        ItemList[index]->Use(*target);
        delete ItemList[index];
        ItemList.erase(ItemList.begin() + index);
        return true;
    }

    void InventoryManager::ShowInventory() {
        if (ItemList.empty()) {
            std::cout << "아이템이 없습니다.\n";
            return;
        }
        for (int i = 0; i < ItemList.size(); i++) {
            std::cout << "[" << i << "] " << ItemList[i]->GetName() << " : " << ItemList[i]->GetItemInfo() << ")\n";
        }
    }

