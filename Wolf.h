#pragma once

#include "Monster.h"

Dice WolfDice;

class Wolf : public Character {
public:
	Wolf() : Monster(HP, WolfDice) {};

private:


};
