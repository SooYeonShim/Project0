#pragma once
#include "Action.h"
#include "StatusEffect.h"


class Cure :
    public Action
{

public:
    virtual void PrintInfo() override;
    virtual void DoActive() override;
    
    Cure();
    virtual Action* Clone() override { return new Cure; }
};
