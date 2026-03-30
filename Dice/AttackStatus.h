#pragma once
#include "Action.h"
#include "StatusEffect.h"
#include <vector>

class AttackStatus : public Action
{
private:
	int power;
	std::vector<StatusEffect> onHitStatuses;

public:

    std::string GetActionName() override { return Action::GetActionName() + "(" + std::to_string(power) + ")"; }
	virtual void PrintInfo() override;
	virtual void DoActive() override;

    AttackStatus(int attackPower, const std::vector<StatusEffect>& statuses);
    virtual Action* Clone() override { return new AttackStatus(*this); }
};
