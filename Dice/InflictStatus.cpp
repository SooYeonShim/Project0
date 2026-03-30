#include "InflictStatus.h"
#include "Character.h"
#include <iostream>



InflictStatus::InflictStatus(const vector<StatusEffect>& Status)
	: Action("InflictStatus", TargetType::ENEMY)
	, effectStatus(Status)
{
}

string InflictStatus::GetActionName()
{
	if (effectStatus.empty())
		return Action::GetActionName();
	return Action::GetActionName() + "(" + to_string(effectStatus[0].turnsRemaining) + ")";
}

void InflictStatus::PrintInfo()
{
	cout << "대상에게 상태이상을 부여합니다.";
	for (StatusEffect& e : effectStatus)
	{
        cout << "[" << e.name << "] 지속: " << e.turnsRemaining << endl;
	}
}

void InflictStatus::DoActive()
{
	string selfnames;
	for (size_t i = 0; i < vecself.size(); ++i)
	{
        selfnames += vecself[i]->GetName();

        if (i < vecself.size() - 1)
            selfnames += ", ";
	}

    // 타겟들에게 상태이상 부여
	for (Character* target : vectarget)
	{
		if (target->GetIsDead())
		{
			cout << selfnames << "은 대상 없음 또는 사망으로 상태 부여 실패." << endl;
			continue;
		}
		cout << selfnames << "는 " << target->GetName() << " 에게 상태 부여." << endl;
		for (const StatusEffect& tmpl : effectStatus)
		{
            // 대상에게 상태이상 구조체 넣기
			cout << "   [" << tmpl.name << "] 적용 (지속 " << tmpl.turnsRemaining << "라운드)" << endl;
            target->AddStatusEffect(tmpl);
		}
	}
}
