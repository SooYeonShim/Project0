#pragma once
#include "Action.h"
#include "StatusEffect.h"
#include <vector>

class InflictStatus : public Action
{
private:
	std::vector<StatusEffect> effectStatus;

public:

    virtual std::string GetActionName() override;
	virtual void PrintInfo() override;
	virtual void DoActive() override;

    virtual Action* Clone() override { return new InflictStatus(*this); }

    InflictStatus(const std::vector<StatusEffect>& templates);
};
