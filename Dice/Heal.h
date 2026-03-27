#pragma once
#include "Action.h"


class Heal :
    public Action
{
private:
    int power;

public:
    virtual std::string GetActionName() override { return Action::GetActionName() + "(" + std::to_string(power) + ")"; }
    virtual void PrintInfo() override;
    virtual void DoActive() override;

    virtual Action* Clone() { return new Heal(*this); }

public:
    Heal(int _power = 1);
};

