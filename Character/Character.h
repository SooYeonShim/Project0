#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"
#include "Action.h"

using namespace std;

class Character 
{
public:
	Character(int MaxHP, Dice& CharacterDice, string Name) : HP(MaxHP), MaxHP(MaxHP), CharacterDice(CharacterDice), Name(Name), CurrentAction(nullptr), Shield(0) {};

    // Getter
    string GetName();
	int GetHP();
    int GetMaxHP();
    bool GetIsDead() const;
	int GetShield();
	Dice GetDice();
	Action* GetCurrentAction();

    // Setter
    void SetName(string Name);
	void SetHP(int HP);
    void SetMaxHP(int MaxHP);
	void SetShield(int Shield);
	void SetDice(Dice CharacterDice);
	void SetCurrentAction(Action* CurrentAction);

    // Function
    void RollDice();
    void DoActive();
	void DoAction(vector<Character*> target);
    void TakeDamage(int Damage);
    void TakeHeal(int Damage);
    void TakeShield(int Damage);
    void EndTurn();

protected:
    int HP; // 체력
    int MaxHP; // 최대 체력
    // bool IsDead; // 사망 여부 -> HP == 0 판정으로 대체
    int Shield; // 방어력
    Dice CharacterDice; // 고유 주사위

private:
    string Name; // 이름
	Action* CurrentAction; // 이번 턴에 취하는 행동
    // vector<StatusEffect> StatusEffects; // 상태이상 벡터 or 맵
};
