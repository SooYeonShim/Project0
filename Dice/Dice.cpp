#include "Dice.h"

#include <iostream>
#include <random>

#include "Action.h"
#include "None.h"

using namespace std;


Dice::Dice()
{
	vecAction.push_back(new None);
	vecAction.push_back(new None);
	vecAction.push_back(new None);
	vecAction.push_back(new None);
	vecAction.push_back(new None);
	vecAction.push_back(new None);
}

Dice::Dice(const Dice& _Other)
{
    for (Action* action : _Other.vecAction)
    {
        if (action != nullptr)
        {
            this->vecAction.push_back(action->Clone());
        }
    }

}

Dice::~Dice()
{
	// 메모리 삭제
	for (Action* action : vecAction)
	{
		delete action;
	}
	vecAction.clear();
}

Action& Dice::GetRandomAction()
{
	// TODO: 여기에 return 문을 삽입합니다.

	// 난수 생성
	std::random_device rd;
	std::mt19937 g(rd());

	// 범위 지정
	uniform_int_distribution<int> distance(0, 5);

	// 랜덤 결과 출력
	int face = distance(g);

	return *(vecAction[face]);
}

void Dice::SetAction(int _faceNumber, Action* _SetAct)
{
	//예외조건 검사
	if (_faceNumber < 0 && _faceNumber > 5)
	{
		cout << "정상적인 범위가 아닙니다." << endl;
		return;
	}

	if (_SetAct == nullptr)
	{
		cout << "주어진 주사위면이 없습니다." << endl;
		return;
	}

	// 등록하기 전 가지고있던 면 삭제
	delete vecAction[_faceNumber];

	// 새로운 면을 등록
	vecAction[_faceNumber] = _SetAct;
}