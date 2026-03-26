#include "Player.h"


JobType Player::GetJobType() {
    return Job;
}
int Player::GetLevel() {
    return Level;
};
int Player::GetExp() {
    return Exp;
};

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
}
