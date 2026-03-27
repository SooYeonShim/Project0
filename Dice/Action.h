#pragma once

#include <vector>
#include <string>
#include "GameEnums.h"

class Character;

class Action
{
private:
	std::string ActionName;
	TargetType Type;

protected:
    std::vector<Character*> vecself;
    std::vector<Character*> vectarget;

public:
	std::string GetActionName() { return ActionName; }
    TargetType GetTargetType() { return Type; }

    // 필요한거 아니면 호출안하는게좋음 getter setter
    const std::vector<Character*>& GetSelfCharacters() { return vecself; }
    const std::vector<Character*>& GetTatgerCharacters() { return vectarget; }
    void SetSelfCharacters(std::vector<Character*>& _vec) { vecself = _vec; }
    void SetTatgerCharacters(std::vector<Character*>& _vec) { vectarget = _vec; }


    // 타겟 설정만 한 단계
    virtual void DoAciton(std::vector<Character*>& _self, std::vector<Character*>& _target)
    {
        vecself = _self;
        vectarget = _target;
    };
    // 실제 효과 실행
    virtual void DoActive() = 0;
	virtual void PrintInfo() = 0;

    // 새롭게 힙메모리에 만들어 생성해 건네줌
    virtual Action* Clone() = 0;

public:
	Action(std::string _name = "None", TargetType _Type = TargetType::ENEMY)
		: ActionName(_name)
		, Type(_Type)
	{
	};
	virtual ~Action() {};
};

