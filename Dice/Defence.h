#pragma once
#include "Action.h"


class Defence :
    public Action
{
private:
    int power;

public:
    virtual void PrintInfo() override;
    virtual void DoActive() override;

    virtual Action* Clone() { return new Defence(*this); }

public:
    Defence(int _power = 2);
};

