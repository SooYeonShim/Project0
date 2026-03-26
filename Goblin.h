#pragma once
#include "Monster.h"

Dice GoblinDice;

class Goblin : public Monster {
public:
	Goblin() : Monster(12, GoblinDice) {};

private:

};