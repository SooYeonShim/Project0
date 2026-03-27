#include "Attack.h"
#include <iostream>

using namespace std;

#include "Character.h"

Attack::Attack(int _power)
	:Action("Attack", TargetType::ENEMY)
	, power(_power)
{
}

void Attack::PrintInfo()
{
    cout << "적에게"<< power << "의 피해를 줍니다." << endl;
}

void Attack::DoActive()
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

    cout << selfnames << " 가 " << targetnames << " 에게 " << power << "의 피해를 가했습니다." << endl;

    // 단일 타겟에게 피해량만큼 피
    for (int i = 0; i < vectarget.size(); ++i)
    {
        vectarget[i]->TakeDamage(power);
    }
}
