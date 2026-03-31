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

        // 현재 HP 비율에 맞춰 레벨업 시 HP 조정
        float HPRatio = (float)HP / (float)MaxHP;

        MaxHP += 3;

        HP = (int)(MaxHP * HPRatio);

        cout << "레벨 업!" << Name << "의 레벨이 " << Level << "로 올랐습니다! [최대 체력 3 증가]" << endl;

        // NextLevelExp += NextLevelExp/4; 레벨링
        this->Exp -= NextLevelExp;
    }
}
void Player::SetNextLevelExp(int NextLevelExp)
{
    this->NextLevelExp = NextLevelExp;
}

void Player::EndTurn()
{

    // 출혈 체크
    auto it = std::find_if(StatusEffects.begin(), StatusEffects.end(),
        [](const StatusEffect& effect) {
            return effect.kind == StateType::BLEED
                && effect.turnsRemaining > 0;
        }
    );

    // 출혈 중이면 피해 적용
    if (it != StatusEffects.end())
    {
        int damage = this->MaxHP / 10;

        if (damage <= 0)
            damage = 1;

        this->HP -= damage;

        cout << Name << "의 출혈 피해: " << damage << endl;
    }

    // 상태 이상 남은 턴 감소
    for (auto it = StatusEffects.begin(); it != StatusEffects.end(); )
    {
        if (it->turnsRemaining > 0)
        {
            --(it->turnsRemaining);
        }

        if (it->turnsRemaining == 0)
        {
            it = StatusEffects.erase(it);
        }
        else
        {
            ++it;
        }
    }

    this->Shield = 0;
    CurrentAction = nullptr;
}
