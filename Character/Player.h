#pragma once
#include "Character.h"
#include "GameEnums.h"

class Player : public Character
{
public:
	Player(int HP, Dice& CharacterDice, string Nickname, JobType Job): Character(HP, CharacterDice, Nickname), Job(Job), Level(0), Exp(0)  {};
	JobType GetJobType();
	int GetLevel();
	int GetExp();
	void SetJobType(JobType job);
	void SetLevel(int Level);
	void SetExp(int Exp);

    


private:
	JobType Job;
	int Level;
	int Exp;
};
