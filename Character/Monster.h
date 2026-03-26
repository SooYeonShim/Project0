#pragma once
#include "Character.h"


class Monster : public Character {
public:
	Monster(int HP, Dice& CharacterDice) : Character(HP, CharacterDice) {};

private:


};
