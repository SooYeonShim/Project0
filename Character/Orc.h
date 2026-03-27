#pragma once
#include "Monster.h"

class Orc : public Monster {
public:
	Orc(Dice& MonsterDice) : Monster(30, MonsterDice, "오크") {};

private:

};
