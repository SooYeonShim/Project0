#include "Heal.h"
#include <iostream>

using namespace std;

#include "Character.h"

Heal::Heal(int _power)
    :Action("Heal", TargetType::FRIENDLY)
    , power(_power)
{
}

void Heal::DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target)
{
    // 타겟이된 아군에게 힐
    int targetHP = _target[0]->GetHP();
    targetHP += power;
    _target[0]->SetHP(targetHP);
}

void Heal::PrintInfo()
{
    cout << "대상을 회복시킵니다. " << power << "만큼 hp가 회복합니다." << endl;
}
