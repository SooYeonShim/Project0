#pragma once
#include "Action.h"


class Defence :
    public Action
{
private:
    int power;

public:
    virtual void DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target) override;
    virtual void PrintInfo() override;

    virtual Action* Clone() { return new Defence(*this); }

public:
    Defence(int _power = 2);
};

