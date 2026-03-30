#include "Character.h"


string Character::GetName() {
	return Name;
}
int Character::GetHP() {
	return HP;
}

int Character::GetMaxHP() {
	return MaxHP;
}

bool Character::GetIsDead() const {
    return HP == 0;
}

int Character::GetShield() 
{
	return Shield;
}
vector<StatusEffect> Character::GetStatusEffects()
{
	return StatusEffects;
}

Dice Character::GetDice()
{
	return CharacterDice;
}

Action* Character::GetCurrentAction()
{
	return CurrentAction;
}

void Character::SetName(string Name)
{
	this->Name = Name;
}
void Character::SetHP(int HP)
{
	this->HP = HP;
}

void Character::SetMaxHP(int MaxHP)
{
	this->MaxHP = MaxHP;
}

void Character::SetShield(int Shield)
{
	this->Shield = Shield;
}

void Character::SetStatusEffects(const vector<StatusEffect>& StatusEffects)
{
	this->StatusEffects = StatusEffects;
}

void Character::SetDice(Dice CharacterDice)
{
	this->CharacterDice = CharacterDice;
}

void Character::SetCurrentAction(Action* CurrentAction)
{
	this->CurrentAction = CurrentAction;
}

void Character::RollDice()
{
    // 주사위의 GetRandomAction 메서드를 호출해 현재 액션에 저장
   CurrentAction = &CharacterDice.GetRandomAction();
}

//
void Character::DoActive()
{
    // 액션 실행 전 상태 체크
    auto it = std::find_if(StatusEffects.begin(), StatusEffects.end(),
        [](const StatusEffect& effect) {
            return effect.kind == StateType::STUN
                && effect.turnsRemaining > 0;
        }
    );

    if (it != StatusEffects.end()) {
        cout << "스턴에 걸려 움직일 수 없습니다." << endl;
    }
     else
     {
        CurrentAction->DoActive();
     }
}

// 할당된 액션 실행
void Character::DoAction(vector<Character*> target)
{
    if (CurrentAction != nullptr)
    {
        // 본 객체의 주소를 vector에 넣고 타겟 캐릭터에 대해 액션 실행
        std::vector<Character*> self;
        self.push_back(this);

        CurrentAction->DoAciton(self, target);
    }
}
// 대미지 입음
void Character::TakeDamage(int Damage)
{
    // 실드 처리
    if (Damage >= Shield) {
        Damage -= Shield;
        Shield = 0;
    }
    else {
        Shield -= Damage;
        Damage = 0;
    }

    // 대미지 적용
    cout << Name << "의 총 피해량: " << Damage << endl;
    HP = max(0, HP - Damage); // max로 0 이하 방지
}

// 체력 회복
void Character::TakeHeal(int heal)
{
    if (heal <= 0) return;

    int prevHP = HP;
    HP = std::min(HP + heal, MaxHP);

    std::cout << Name
        << " 회복: " << (HP - prevHP)
        << " (현재 HP: " << HP << "/" << MaxHP << ")\n";
}

// 실드 적용
void Character::TakeShield(int Shield_)
{
    if (Shield_ <= 0) return; // 방어

    this->Shield += Shield_;

    std::cout << Name
        << " 방어도 증가: " << Shield_
        << " (현재 방어도: " << this->Shield << ")\n";

}

// 턴 종료시 호출하는 함수
void Character::EndTurn()
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

        cout << "출혈 피해: " << damage << endl;
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
