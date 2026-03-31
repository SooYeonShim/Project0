#pragma once
#include "Monster.h"

class Orc : public Monster {
public:
	Orc(Dice& MonsterDice) : Monster(22, MonsterDice, "오크") {};

private:

};
