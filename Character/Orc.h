#pragma once
#include "Monster.h"

Dice OrcDice;

class Goblin : public Monster {
public:
	Goblin() : Monster(30, OrcDice) {};

private:

};