#pragma once
#include "Action.h"

class None :
	public Action
{
public:
	virtual void PrintInfo() override;
    virtual void DoActive() override;

    virtual Action* Clone() { return new None(*this); }

public:
	None();
};

