#include "Defence.h"

#include <iostream>
#include "Character.h"

using namespace std;

Defence::Defence(int _power)
    :Action("Defence", TargetType::MYSELF)
    , power(_power)
{
}

void Defence::DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target)
{
    // 자기자신에게 쉴드 추가
    int currentshield = _self[0]->GetShield();
    currentshield += power;
    _self[0]->SetShield(currentshield);
}

void Defence::PrintInfo()
{
    cout << "공격에 대비합니다. " << power << "만큼 쉴드가 증가합니다." << endl;
}
