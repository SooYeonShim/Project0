#pragma once

#include <map>
#include <string>
#include <vector>
#include "Player.h"
#include "Dice.h"

#include "Goblin.h"
#include "Orc.h"
#include "Wolf.h"
#include "HealingPotion.h"

using namespace std;

class Action;

class TemplateManager
{
private:
    // 등록된 액션
    std::vector<Action*> Actionlists;

    // 상점판매용 액션
    std::vector<Action*> ShopActionlists;

    // 액션이 등록되어잇나 확인용
    bool IsActionlists = false;

public:
    static TemplateManager& getInstance()
    {
        static TemplateManager instance; // 최초 1회만 생성
        return instance;
    }

public:
    // 초기 생성, 몬스터
    Goblin GetMonsterByGoblin();
    Orc GetMonsterByOrc();
    Wolf GetMonsterByWolf();

    Dice GetDiceByGobline();
    Dice GetDiceByOrc();
    Dice GetDiceByWolf();

    // 직업 주사위
    Dice GetDiceByWarrior();
    Dice GetDiceByArcher();
    Dice GetDiceByDefender();
    Dice GetDiceByRogue();

    // 직업타입을 주면 직업주사위반환
    Dice GetDiceByType(JobType _type);

    // 직업 타입을 주면 직업 반환
    Player GetPlayerByType(string Nickname, JobType _type);

    // 아이템 생성
    // 주의! 해당 포인터는 힙메모리에 있고 명확한 소유주가 없기에 메모리관리를 주의해야함
    Item* GetHealingPotion();

    // action리스트 초기화
    void InitActions();

    // 상점 UI용, 판매 액션 목록 출력
    void PrintShopActionList();

    // 만일 UI커스텀을 원한다면 상점의 액션리스트 전부 보내주기용도
    const std::vector<Action*> GetShopActionList() const { return ShopActionlists; }

    // 상점 구매용, 액션 이름으로 검색해서 새 인스턴스 반환(없으면 nullptr)
    // 주의! 해당 포인터는 힙메모리에 있고 명확한 소유주가 없기에 메모리관리를 주의해야함
    Action* CreateActionByName(const std::string& actionName);

private:
    // 생성자를 private으로 막음
    TemplateManager() {}
    ~TemplateManager();

    // 복사/대입도 막음
    TemplateManager(const TemplateManager&) = delete;
    TemplateManager& operator=(const TemplateManager&) = delete;
};

