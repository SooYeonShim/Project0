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
    // 단일적이냐 모든적이냐에 따라 구별
    string target = "적에게 ";
    if (GetTargetType() == TargetType::ENEMYALL)
        target = "모든 적에게 ";


    cout << target << power << "의 피해를 줍니다." << endl;
}

void Attack::DoActive()
{
    // UI출력
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


    int calculPower = power;
    if (!vecself.empty())
    {
        // 플레이어에게 피해량 증가옵션이 추가된다면...
    }

    // 단일 타겟에게 피해량만큼 피
    for (int i = 0; i < vectarget.size(); ++i)
    {
        if (vectarget[i]->GetIsDead())
        {
            cout << selfnames << " 가 " << targetnames << " 에게 공격하려 했으나 대상은 이미 쓰러져 있습니다." << endl;
        }
        else
        {
            cout << selfnames << " 가 " << targetnames << " 에게 " << calculPower << "의 피해를 가했습니다." << endl;
            vectarget[i]->TakeDamage(calculPower);
        }
    }
}
