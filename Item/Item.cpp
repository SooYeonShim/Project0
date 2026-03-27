#include "Item.h"

string Item::GetName() {
    return this->Name;
}

int Item::GetPrice() {
    return this->Price;
}

string Item::GetItemInfo() {
    return this->ItemInfo;
}

void Item::SetName(string Name) {
    this->Name = Name;
}

void Item::SetPrice(int Price) {
    this->Price = Price;
}

void Item::SetItemInfo(string ItemInfo) {
    this->ItemInfo = ItemInfo;
}
