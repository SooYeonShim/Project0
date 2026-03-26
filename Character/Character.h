#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"
#include "Action.h"

using namespace std;

class Character 
{
public:
	Character(int MaxHP, Dice& CharacterDice) : HP(MaxHP), MaxHP(MaxHP), CharacterDice(CharacterDice) {};

    // Getter
	int GetHP();
    int GetMaxHP();
    bool GetIsDead();
	int GetShield();
	Dice GetDice();
	Action* GetCurrentAction();

    // Setter
	void SetHP(int HP);
    void SetMaxHP(int MaxHP);
    void SetIsDead(bool IsDead);
	void SetShield(int Shield);
	void SetDice(Dice CharacterDice);
	void SetCurrentAction(Action* CurrentAction);

    // Function
	void RollDice();
	void DoAction(vector<Character*> target);
	
private:
	int HP; // 체력
    int MaxHP; // 최대 체력
    bool IsDead; // 사망 여부
	int Shield; // 방어력
	Dice CharacterDice; // 고유 주사위
	Action* CurrentAction; // 이번 턴에 취하는 행동
};
