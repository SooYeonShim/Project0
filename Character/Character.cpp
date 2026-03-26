#include "Character.h"


int Character::GetHP() {
	return HP;
}

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

void Character::SetHP(int HP)
{
	this->HP = HP;
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
    Action* CurrentAction = &CharacterDice.GetRandomAction();
}
void Character::DoAction(vector<Character*> target)
{
    // 본 객체의 주소를 vector에 넣고 타겟 캐릭터에 대해 액션 실행
    std::vector<Character*> self;
    self.push_back(this);
    CurrentAction->DoAciton(self, target);
}
