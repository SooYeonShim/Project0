#include "Player.h"


JobType Player::GetJobType()
{
    return Job;
}
int Player::GetLevel()
{
    return Level;
}
int Player::GetExp()
{
    return Exp;
}
int Player::GetNextLevelExp()
{
    return NextLevelExp;
}

void Player::SetJobType(JobType Job)
{
    this->Job = Job;
}
void Player::SetLevel(int Level)
{
    this->Level = Level;
}
void Player::SetExp(int Exp)
{
    this->Exp = Exp;
    // 레벨 업
    if (Exp >= NextLevelExp)
    {
        ++Level;
        MaxHP += 3;
        // NextLevelExp += NextLevelExp/4; 레벨링
        this->Exp -= NextLevelExp;
    }
}
void Player::SetNextLevelExp(int NextLevelExp)
{
    this->NextLevelExp = NextLevelExp;
}
