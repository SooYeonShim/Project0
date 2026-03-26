#pragma once
#include "Character.h"
#include "Monster.h"

class Wolf : public Monster {
public:
	Wolf(Dice& MonsterDice) : Monster(8, MonsterDice) {};

private:


};
