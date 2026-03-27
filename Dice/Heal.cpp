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
    cout << "아군에게 " << power << "만큼 hp가 회복합니다." << endl;
}

void Heal::DoActive()
{
    string selfnames = "?";
    string targetnames = "?";

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

    cout << selfnames << "는 대상을 회복시킵니다. " << targetnames << "는 " << power << "만큼 hp가 회복합니다." << endl;

    // 타겟이된 아군에게 힐
    for (int i = 0; i < vectarget.size(); ++i)
    {
        vectarget[i]->TakeHeal(power);
    }
}
