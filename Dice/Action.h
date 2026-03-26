#pragma once

enum class TargetType
{
	ENEMY,
	FRIENDLY,
	MYSELF
};

#include <vector>
#include <string>

class Character;

class Action
{
private:
	std::string ActionName;
	TargetType Type;

public:
	std::string GetActionName() { return ActionName; }
	virtual void DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target) = 0;
	virtual void PrintInfo() = 0;

public:
	Action(std::string _name = "None", TargetType _Type = TargetType::ENEMY)
		: ActionName(_name)
		, Type(_Type)
	{
	};
	virtual ~Action() {};
};

