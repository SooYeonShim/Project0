#include "Player.h"

string Player::GetNickname() {
    return Nickname;
}
JobType Player::GetJobType() {
    return Job;
}
int Player::GetLevel() {
    return Level;
};
int Player::GetExp() {
    return Exp;
};
void Player::SetNickname(string Nickname)
{
    this->Nickname = Nickname;
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
}
