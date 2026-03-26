#pragma once
#include "Character.h"
#include "GameEnums.h"

class Player : public Character
{
public:
	Player(int HP, Dice CharacterDice, string Nickname, JobType Job): Character(HP, CharacterDice), Nickname(Nickname), Job(Job) {};
    string GetNickname() { return Nickname; }
    JobType GetJobType() { return Job; }
	int GetLevel();
	int GetExp();
	void SetNickname(string Nickname);
	void SetJobType(JobType job);
	void SetLevel(int Level);
	void SetExp(int Exp);

    


private:
	string Nickname;
	JobType Job;
	int Level;
	int Exp;
};
