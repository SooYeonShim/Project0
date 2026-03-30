#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Character.h"

using namespace std;

class Item
{
public:
    Item(string Name, int Price, string ItemInfo): Name(Name), Price(Price), ItemInfo(ItemInfo){};

    // Getter
    string GetName();
    int GetPrice();
    string GetItemInfo();

    // Setter
    void SetName(string Item);
    void SetPrice(int Price);
    void SetItemInfo(string ItemInfo);

    virtual bool Use(Character& target) = 0;

private:
    string Name;
    int Price;
    string ItemInfo;
    
};

