#pragma once
#include "Monster.h"

class Goblin : public Monster {
public:
	Goblin(Dice& MonsterDice) : Monster(12, MonsterDice, "고블린") {};

private:
    
};
