#pragma once
#include "Action.h"

class None :
	public Action
{
public:
	virtual void DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target) override {};
	virtual void PrintInfo() override;

    virtual Action* Clone() { return new None(*this); }

public:
	None();
};

