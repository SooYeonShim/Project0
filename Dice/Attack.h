#pragma once
#include "Action.h"


class Attack :
	public Action
{
private:
	int power;

public:
	virtual void DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target) override;
	virtual void PrintInfo() override;

    virtual Action* Clone() { return new Attack(*this); }

public:
	Attack(int _power = 1);

};

