#pragma once
#include "Character.h"
#include "GameEnums.h"

class Player : public Character
{
public:
    Player(int HP, Dice& CharacterDice, string Nickname, JobType Job): Character(HP, CharacterDice, Nickname), Job(Job), Level(0), Exp(0), NextLevelExp(30)  {};

    // Getter
    JobType GetJobType();
	int GetLevel();
	int GetExp();
    int GetNextLevelExp();

    // Setter
	void SetJobType(JobType job);
	void SetLevel(int Level);
	void SetExp(int Exp);
    void SetNextLevelExp(int NextLevelExp);

    void EndTurn() override;
    
private:
	JobType Job; // 직업
	int Level; // 현재 레벨
	int Exp; // 현재 경험치
    int NextLevelExp; // 다음 레벨까지 필요한 경험치
};
