#pragma once
#include <vector>
#include "Item.h"

using namespace std;

class Inventory
{
public:
    Inventory() : MaxCapacity(3) {};
    Item* AddItem(Item* Item);
    void UseItem(int n);

    

private:
    vector<Item*> ItemList;
    int MaxCapacity;
};

