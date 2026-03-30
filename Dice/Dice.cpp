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
    if (_faceNumber < 0 || _faceNumber > 5)
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

Action& Dice::GetAction(int _faceNumber)
{
    if (_faceNumber < 0 || _faceNumber > 5)
    {
        cout << "정상적인 범위가 아닙니다." << endl;
        return;
    }

    return *vecAction[_faceNumber];
}

void Dice::PrintActionInfo()
{
    const int width = 15; // 가로 길이를 15로 고정

    // 1. 선과 공백을 width에 맞춰 동적으로 생성 (수동 입력 방지)
    const std::string hLine = "+" + std::string(width, '-');  // "+---------------"
    const std::string indent(width + 1, ' ');                // "                "
    const std::string emptyLine = "|" + std::string(width, ' ') + "|"; // "|               |"

    // 중단 전용 빈 줄 (4칸 연속)
    const std::string midEmpty = emptyLine + std::string(width, ' ') + "|" + std::string(width, ' ') + "|" + std::string(width, ' ') + "|";

    auto getName = [&](int index) -> std::string {
        if (index >= 0 && index < (int)vecAction.size() && vecAction[index] != nullptr) {
            return std::to_string(index + 1) + ". " + vecAction[index]->GetActionName();
        }
        return std::to_string(index + 1) + ". Empty";
        };

    std::cout << "\n[ Dice Net Layout ]" << std::endl;

    // --- 1. 상단 (0번 면) ---
    std::cout << indent << hLine << "+" << std::endl;
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << "| " << std::setw(width - 2) << std::left << getName(0) << " |" << std::endl;
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << emptyLine << std::endl;

    // --- 2. 중단 (1, 2, 3, 4번 면) ---
    std::cout << hLine << hLine << hLine << hLine << "+" << std::endl;
    std::cout << midEmpty << std::endl;
    std::cout << midEmpty << std::endl;

    std::cout << "| " << std::setw(width - 2) << std::left << getName(1) << " | "
        << std::setw(width - 2) << std::left << getName(2) << " | "
        << std::setw(width - 2) << std::left << getName(3) << " | "
        << std::setw(width - 2) << std::left << getName(4) << " |" << std::endl;

    std::cout << midEmpty << std::endl;
    std::cout << midEmpty << std::endl;
    std::cout << hLine << hLine << hLine << hLine << "+" << std::endl;

    // --- 3. 하단 (5번 면) ---
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << "| " << std::setw(width - 2) << std::left << getName(5) << " |" << std::endl;
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << emptyLine << std::endl;
    std::cout << indent << hLine << "+" << std::endl;

    std::cout << "\n[ ACTION DETAILS ]" << std::endl;
    for (int i = 0; i < (int)vecAction.size(); ++i)
    {
        if (vecAction[i] != nullptr)
        {
            std::cout << i+1 << ". [" << vecAction[i]->GetActionName() << "] : ";
            vecAction[i]->PrintInfo(); // 각 액션 클래스에서 구현한 상세 설명 호출
        }
        else
        {
            std::cout << i+1 << ". [Empty]" << std::endl;
        }
    }
    std::cout << "---------------------------------------------\n" << std::endl;
}

void Dice::PrintActionSmallInfo()
{
    for (int i = 0; i < (int)vecAction.size(); ++i)
    {
        if (vecAction[i] != nullptr)
        {
            std::cout << i + 1 << ". [" << vecAction[i]->GetActionName() << "] : ";
            vecAction[i]->PrintInfo(); // 각 액션 클래스에서 구현한 상세 설명 호출
        }
        else
        {
            std::cout << i + 1 << ". [Empty]" << std::endl;
        }
    }
    std::cout << "---------------------------------------------\n" << std::endl;
}
