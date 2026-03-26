#pragma once
#include "Character.h"
#include "GameEnums.h"

class Player : public Character
{
public:
	Player(string Nickname, JobType Job): Nickname(Nickname), Job(Job) {};
	string GetNickname();
	JobType GetJobType();
	int GetLevel();
	int GetExp();
	void SetNickname(string Nickname);
	void SetJobType(JobType job);
	void SetLevel(int level);
	void SetExp(int Exp);

private:
	string Nickname;
	JobType Job;
	int level;
	int Exp;
};