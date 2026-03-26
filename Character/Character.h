#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"
#include "Action.h"

using namespace std;

class Character 
{
public:
	Character(int HP, Dice CharacterDice) : HP(HP), CharacterDice(CharacterDice) {};
	int GetHP();
	int GetShield();
	Dice GetDice();
	Action* GetCurrentAction();
	void SetHP(int HP);
	void SetShield(int Shield);
	void SetDice(Dice CharacterDice);
	Action* SetCurrentAction(Action* CurrentAction);

	void RollDice();
	void DoAction(vector<Character*> target);
	
private:
	int HP;
	int Shield;
	Dice CharacterDice;
	Action* CurrentAction;
};
