#pragma once
#include "Monster.h"

Dice WolfDice;

class Wolf : public Monster {
public:
	Wolf() : Monster(8, WolfDice) {};

private:


};
