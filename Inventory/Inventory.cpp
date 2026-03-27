#include "Inventory.h"

Item* Inventory::AddItem(Item* Item) {
    {
        ItemList.push_back(Item);
        return ItemList.back();
    }

}

void Inventory::UseItem(int n) {
    cout << "아이템 사용" << endl;
}
