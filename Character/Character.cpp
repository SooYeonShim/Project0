#include "Character.h"


int Character::GetHP() {
	return HP;
}

int Character::GetShield() 
{
	return Shield;
}

Dice Character::GetDice()
{
	return CharacterDice;
}

Action Character::GetCurrentAction()
{
	return CurrentAction;
}

void Character::SetHP(int HP)
{
	this->HP = HP;
}

void Character::SetShield(int Shield)
{
	this->Shield = Shield;
}

void Character::SetDice(Dice CharacterDice)
{
	this->CharacterDice = CharacterDice;
}

Action Character::SetCurrentAction(Action CurrentAction)
{
	this->CurrentAction = CurrentAction;
}