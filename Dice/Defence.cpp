#include "Defence.h"

#include <iostream>
#include "Character.h"

using namespace std;

Defence::Defence(int _power)
    :Action("Defence", TargetType::MYSELF)
    , power(_power)
{
}

void Defence::PrintInfo()
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

    cout << selfnames <<"는 공격에 대비합니다. " << power << "만큼 쉴드가 증가합니다." << endl;
}

void Defence::DoActive()
{
    // 자기자신에게 쉴드 추가
    for (int i = 0; i < vecself.size(); ++i)
    {
        int currentshield = vecself[i]->GetShield();
        currentshield += power;
        vecself[i]->SetShield(currentshield);
    }
}
