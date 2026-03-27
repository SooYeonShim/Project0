#pragma once
#include "Action.h"


class Defence :
    public Action
{
private:
    int power;

public:
    virtual std::string GetActionName() override { return Action::GetActionName() + "(" + std::to_string(power) + ")"; }
    virtual void PrintInfo() override;
    virtual void DoActive() override;

    virtual Action* Clone() { return new Defence(*this); }

public:
    Defence(int _power = 4);
};

