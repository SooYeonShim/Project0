#include "Cure.h"
#include "Character.h"

Cure::Cure()
    :Action("Cure", TargetType::FRIENDLY)
{
}

void Cure::PrintInfo()
{
    string target = "아군의 ";
    if (GetTargetType() == TargetType::FRIEDLYALL)
        target = "모든 아군의 ";

    cout << target << "헤로운 상태이상을 회복합니다." << endl;
}

void Cure::DoActive()
{
    string selfnames = "";

    // 공격자 이름 추출
    for (int i = 0; i < vecself.size(); ++i)
    {
        selfnames += vecself[i]->GetName();

        if (i < vecself.size() - 1)
            selfnames += ", ";
    }

    // 타겟들의 상태이상 치유
    for (Character* target : vectarget)
    {
        if (!target || target->GetIsDead())
        {
            cout << selfnames << " 가 " << target->GetName() << " 에게 회복하려 했으나 쓰러진 대상은 치유가 불가능합니다." << endl;
            continue;
        }
        cout << selfnames << "는 " << target->GetName() << " 의 상태이상을 해제한다." << endl;

        // 캐릭터의 상태를 해제한다.
        // 해제될 상태이상 : STUN, DEMAGEINCREASE, BLEED

    }

}
