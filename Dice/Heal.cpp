#include "Heal.h"
#include <iostream>

using namespace std;

#include "Character.h"

Heal::Heal(int _power)
    :Action("Heal", TargetType::FRIENDLY)
    , power(_power)
{
}

void Heal::PrintInfo()
{
    // 단일이냐 모든이냐에 따라 구별
    string target = "아군에게 ";
    if (GetTargetType() == TargetType::FRIEDLYALL)
        target = "모든 아군에게 ";

    cout << target << power << "만큼 hp가 회복합니다." << endl;
}

void Heal::DoActive()
{
    string selfnames = "";
    string targetnames = "";

    // 공격자 이름 추출
    for (int i = 0; i < vecself.size(); ++i)
    {
        selfnames += vecself[i]->GetName();

        if (i < vecself.size() - 1)
            selfnames += ", ";
    }
    // 타겟 이름 추출
    for (int i = 0; i < vectarget.size(); ++i)
    {
        targetnames += vectarget[i]->GetName();

        if (i < vectarget.size() - 1)
            targetnames += ", ";
    }

    // 타겟이된 아군에게 힐
    for (int i = 0; i < vectarget.size(); ++i)
    {
        if (vectarget[i]->GetIsDead())
        {
            cout << selfnames << " 가 " << targetnames << " 에게 회복하려 했으나 쓰러진 대상은 치유가 불가능합니다." << endl;
        }
        else
        {
            cout << selfnames << "는 " << targetnames << "에게 " << power << "만큼 회복시킵니다." << endl;
            vectarget[i]->TakeHeal(power);
        }
    }
}
