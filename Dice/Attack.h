#pragma once
#include "Action.h"


class Attack :
	public Action
{
private:
	int power;

public:
    // "Attack(5)" 같은 형식으로 이름 반환
    virtual std::string GetActionName() override { return Action::GetActionName() + "(" + std::to_string(power) + ")"; }


	virtual void PrintInfo() override;
    virtual void DoActive();

    virtual Action* Clone() { return new Attack(*this); }

public:
	Attack(int _power = 3);

};

