#pragma once
#include "Action.h"


class Attack :
	public Action
{
private:
	int power;

public:
	virtual void PrintInfo() override;
    virtual void DoActive();

    virtual Action* Clone() { return new Attack(*this); }

public:
	Attack(int _power = 1);

};

