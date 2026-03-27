#pragma once
#include <algorithm>
#include "Item.h"
class HealingPotion : public Item
{
public:
    HealingPotion() : Item("힐링 포션", 20, "체력을 5 회복합니다.") {};
    void Use(Character& target);

private:
};

