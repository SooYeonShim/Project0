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
	Action GetCurrentAction();
	void SetHP(int HP);
	void SetShield(int SetShield);
	void SetDice(Dice dice);
	Action SetCurrentAction();

	void RollDice();
	void DoAction(vector<Character> target);
	
private:
	int HP;
	int Shield;
	Dice CharacterDice;
	Action CurrentAction;
};