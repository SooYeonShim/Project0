#pragma once
#include "Character.h"


class Monster : public Character {
public:
	Monster(int HP, Dice& CharacterDice, string Name) : Character(HP, CharacterDice, Name) {};

private:


};
