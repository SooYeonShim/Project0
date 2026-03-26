#pragma once
#include "Action.h"


class Heal :
    public Action
{
private:
    int power;

public:
    virtual void DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target) override;
    virtual void PrintInfo() override;

public:
    Heal(int _power = 1);
};

