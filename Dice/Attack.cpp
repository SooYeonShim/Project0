#include "Attack.h"
#include <iostream>

using namespace std;

#include "Character.h"

Attack::Attack(int _power)
	:Action("Attack", TargetType::ENEMY)
	, power(_power)
{
}


void Attack::DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target)
{
	// 단일 타겟에게 피해량만큼 피해
	int EnemyHP = _target[0]->GetHP();
	EnemyHP -= power;
	_target[0]->SetHP(EnemyHP);
}

void Attack::PrintInfo()
{
	cout << "적에게 " << power << "의 피해를 입힙니다." << endl;
}