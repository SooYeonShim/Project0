#pragma once
#include "Monster.h"

class Troll : public Monster {
public:
    Troll(Dice& MonsterDice) : Monster(30, MonsterDice, "트롤") {};

private:

};
