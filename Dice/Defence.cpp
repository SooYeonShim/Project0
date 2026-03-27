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
    cout << "아군에게" << power << "의 쉴드를 줍니다." << endl;
}

void Defence::DoActive()
{
    // UI출력
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


    // 자기자신에게 쉴드 추가
    for (int i = 0; i < vecself.size(); ++i)
    {
        if (vecself[i]->GetIsDead())
        {
            cout << selfnames << "는 이미쓰러져 방어가 불가능합니다." << endl;
        }
        else
        {
            cout << selfnames << "는 공격에 대비합니다." << endl;
            vecself[i]->TakeShield(power);
        }
    }
}
