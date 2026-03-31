#pragma once
#include <vector>
#include <memory>

#include "Action.h"

class Dice
{
private:
    std::vector<Action*> vecAction;

public:
	// 다이스면을 전부 받아옵니다.
	std::vector<Action*>& GetActionlist() { return vecAction; }

	// 랜덤한 다이스면의 결과를 반환합니다.
	Action& GetRandomAction();

	// 다이스면을 등록합니다. 기존자리의 면은 삭제됩니다.
	void SetAction(int _faceNumber, Action* _SetAct);

    // 다이스 면의 포인터를 가져옵니다.
    // 주의) delete하지 말 것. Dice가 관리함
    Action* GetAction(int _faceNumber);

    // 면들의 정보를 출력합니다.
    void PrintActionInfo();

    // 면들의 정보를 간략하게 출력합니다.
    void PrintActionSmallInfo();

public:
	Dice();
    Dice(const Dice& _Other);

	~Dice();

    Dice& operator=(const Dice& _Other)
    {
        for (Action* action : vecAction)
        {
            delete action;
        }
        vecAction.clear();

        for (Action* action : _Other.vecAction)
        {
            if (action != nullptr)
            {
                this->vecAction.push_back(action->Clone());
            }
        }

        return *this;
    }
};
