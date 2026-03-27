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

//bool Character::GetIsDead() {
//    return IsDead;
//}

int Character::GetShield() 
{
	return Shield;
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

//void Character::SetIsDead(bool IsDead)
//{
//	this->IsDead = IsDead;
//}

void Character::SetMaxHP(int MaxHP)
{
	this->MaxHP = MaxHP;
}

void Character::SetShield(int Shield)
{
	this->Shield = Shield;
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
    // 대미지 계산
    int Damage_ = Damage - Shield;

    // 실드가 데미지보다 크면 0 대미지로 처리
    if (Damage_ < 0)
    {
        Damage_ = 0;
    }

    // 대미지 적용
    cout << Name << "의 총 피해량: " << Damage_ << endl;
    HP = HP - Damage_;

    // HP는 최저 0으로 관리
    // 죽은 상태는 HP == 0 여부로 판단
    if (HP <= 0)
    {
        HP = 0;
    }
}

// 체력 회복
void Character::TakeHeal(int Heal)
{
    cout << Name << "의 회복량: " << HP << endl;
    // HP 회복
    // 최대 체력 한도까지 회복 가능
    HP = HP + Heal;
    if (HP > MaxHP)
    {
        HP = MaxHP;
    }
}
// 실드 적용
void Character::TakeShield(int Shield)
{
    // 실드 중첩
    this->Shield += Shield; 
    cout << Name << "의 방어도: " << this->Shield << endl;
}

// 턴 종료시 호출하는 함수
void Character::EndTurn()
{
    this->Shield = 0;
}
