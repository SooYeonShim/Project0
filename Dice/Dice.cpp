#include "Dice.h"

#include <iostream>
#include <random>
#include <iomanip>

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

void Dice::PrintActionInfo()
{
    // 한 칸의 너비
    const int width = 14;

    // 인덱스와 이름을 합
    auto getNameWithIndex = [&](int index) -> std::string
        {
            if (index >= 0 && index < vecAction.size() && vecAction[index] != nullptr)
            {
                // "0. Attack" 형태로 합치기
                return std::to_string(index) + ". " + vecAction[index]->GetActionName();
            }
            return std::to_string(index) + ". Empty";
        };

    std::string indent(width + 3, ' ');

    std::cout << "\n[ Dice Action Layout ]" << std::endl;

    // 1. 상단 (0번) 천장
    std::cout << indent << "+----------------+" << std::endl;
    // 1. 상단 (0번) 내용
    std::cout << indent << "| " << std::setw(width) << std::left << getNameWithIndex(0) << " |" << std::endl;

    // 2. 중단 (1, 2, 3, 4) 천장 - 0번의 바닥과 이어짐
    // 0번 아래에만 +--+가 오도록 구성
    std::cout << "+----------------+----------------+----------------+----------------+" << std::endl;

    // 2. 중단 내용
    std::cout << "| " << std::setw(width) << std::left << getNameWithIndex(1) << " | "
        << std::setw(width) << std::left << getNameWithIndex(2) << " | "
        << std::setw(width) << std::left << getNameWithIndex(3) << " | "
        << std::setw(width) << std::left << getNameWithIndex(4) << " |" << std::endl;

    // 2. 중단 바닥 (5번의 천장과 이어짐)
    std::cout << "+----------------+----------------+----------------+----------------+" << std::endl;

    // 3. 하단 (5번) 내용
    std::cout << indent << "| " << std::setw(width) << std::left << getNameWithIndex(5) << " |" << std::endl;
    // 3. 하단 (5번) 바닥
    std::cout << indent << "+----------------+" << std::endl;

    std::cout << "\n[ ACTION DETAILS ]" << std::endl;
    for (int i = 0; i < (int)vecAction.size(); ++i)
    {
        if (vecAction[i] != nullptr)
        {
            std::cout << i << ". [" << vecAction[i]->GetActionName() << "] : ";
            vecAction[i]->PrintInfo(); // 각 액션 클래스에서 구현한 상세 설명 호출
        }
        else
        {
            std::cout << i << ". [Empty]" << std::endl;
        }
    }
    std::cout << "---------------------------------------------\n" << std::endl;
}
