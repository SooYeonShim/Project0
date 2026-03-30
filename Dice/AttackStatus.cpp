#include "AttackStatus.h"
#include "Character.h"
#include <iostream>

AttackStatus::AttackStatus(int attackPower, const vector<StatusEffect>& statuses)
	: Action("Attack+", TargetType::ENEMY)
	, power(attackPower)
	, onHitStatuses(statuses)
{
}

void AttackStatus::PrintInfo()
{
	cout << "적에게 " << power << " 피해 후 상태이상을 부여합니다.";
    for (const StatusEffect& e : onHitStatuses)
    {
        cout << "[" << e.name << "] 지속: " << e.turnsRemaining << endl;
    }
}

void AttackStatus::DoActive()
{
	string selfnames;
	string targetnames;

	for (size_t i = 0; i < vecself.size(); ++i)
	{
		selfnames += vecself[i]->GetName();
		if (i + 1 < vecself.size())
			selfnames += ", ";
	}
	for (size_t i = 0; i < vectarget.size(); ++i)
	{
		targetnames += vectarget[i]->GetName();
		if (i + 1 < vectarget.size())
			targetnames += ", ";
	}

	int calculPower = power;
    if (!vecself.empty())
    {
        // Todo :: 플레이어에게 피해량 증가옵션이 추가된다면...
    }

	for (size_t i = 0; i < vectarget.size(); ++i)
	{
		Character* target = vectarget[i];
		if (target->GetIsDead())
		{
			cout << selfnames << " 가 " << targetnames << " 에게 공격하려 했으나 대상은 이미 쓰러져 있습니다." << endl;
			continue;
		}

        // 피해처리
		cout << selfnames << " 가 " << target->GetName() << " 에게 " << calculPower << "의 피해를 가했습니다." << endl;
		target->TakeDamage(calculPower);

        // 상태이상
		if (!target->GetIsDead())
		{
			for (size_t k = 0; k < onHitStatuses.size(); ++k)
			{
				// Todo :: 대상에게 상태이상 구조체 넣기
				cout << "는 " << target->GetName() << " 에게 [" << onHitStatuses[k].name << "] 부여" << endl;
			}
		}
	}
}
