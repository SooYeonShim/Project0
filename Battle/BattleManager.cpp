#include <sstream>

#include "BattleManager.h"

#pragma region 출력 관련 편의상 만든 함수

static int GetUserInputNum() {
    int choice;
    while (true) 
    {
        std::cout << "명령어 입력 : ";
        std::cin >> choice;

        if (std::cin.fail()) 
        {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else 
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    return choice;
}

static void WaitForEnter(std::string message) 
{
    std::cout << message << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void PrintMessage(std::string message)
{
    std::cout << message << std::endl;
}

static void PrintMenu(const std::vector<std::string>& menus, int width = 30) 
{
    std::string line(width, '=');

    std::cout << line << std::endl;

    for (const std::string& menu : menus) {

        int padding = (width - 4 - menu.length()) / 2;

        std::cout << "== ";

        for (int i = 0; i < padding; ++i)
        {
            std::cout << " ";
        }

        std::cout << menu;

        int currentPos = 4 + padding + menu.length();
        while (currentPos < width - 2) 
        {
            std::cout << " ";
            currentPos++;
        }

        std::cout << " ==" << std::endl;
    }

    std::cout << line << std::endl;
}

static void PrintBattleBoard(vector<Player>& player, vector<Monster>& monster)
{
    std::string line(30, '=');
    std::cout << "현황판" << std::endl;
    std::cout << line << std::endl;
    for (vector<Player>::iterator it = player.begin(); it != player.end(); ++it) {
        cout << it->GetNickname() << "  " << it->GetHP() << " / " << it->GetMaxHP() << std::endl;

    }
    std::cout << std::endl;    
    for (vector<Monster>::iterator it = monster.begin(); it != monster.end(); ++it) {
        // TODO:: 몬스터 종류 이름을 가져오기
        cout << "고블린" << "  " << it->GetHP() << " / " << it->GetMaxHP() << std::endl;
    }
    std::cout << line << std::endl;

}


#pragma endregion

bool BattleManager::Battle(std::vector<Player>& player, int stage)
{
    // 몬스터 생성
    // TODO:: MonsterSpawn으로 교체
    std::vector<Monster> monsters;
    monsters.reserve(3);
    
    for (int i = 0; i < 3; ++i) {
        monsters.push_back(Goblin());
    }

    while (true) 
    {
        // Enemy 
            // Enemy 다이스를 굴림 -> 다이스는 단일
            // 사용은 X, 공격 대상만 보여줌
        
        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it) 
        {
            // 몬스터가 주사위를 굴림
            //it->RollDice();
        }


        int remainRerollCount = RerollCount;

        // Player Turn
        // DICE PHASE

        // 주사위 굴리기
        WaitForEnter("주사위를 굴립니다. ( 게속 하려면 엔터키를 눌러주세요. )");

        bool isDicePhaseFinished = false;

        std::vector<std::string> dicePhaseMenu = { "플레이어 행동", "", "0. 현황판 확인", "1. 주사위 착용하기", "2. 리롤하기", "3. 다음 페이즈로" };              

        while (!isDicePhaseFinished)
        {

            if (remainRerollCount <= 0) 
            {
                break;
            }

            std::stringstream ss;
            ss << "현재 남은 리롤 횟수 : " << remainRerollCount;
            PrintMessage(ss.str());

            PrintMenu(dicePhaseMenu);

            int userInput = GetUserInputNum();

            switch (userInput) 
            {
            case 0:
                // 현황판 출력
                PrintBattleBoard(player, monsters);
                break;
            case 1:
                // 주사위 착용할 수 있게 처리
                break;
            case 2:
                --remainRerollCount;

                // 주사위 새로 굴리기
                WaitForEnter("주사위를 굴립니다. ( 게속 하려면 엔터키를 눌러주세요. )");

                break;
            case 3:
                isDicePhaseFinished = true;
                break;

            default:
                PrintMessage("유효하지 않은 명령입니다.");
                break;
            }
        }


        // 장착되지 않은 주사위 플레이어에게 자동 장착하기

        // TARGET PHASE        
            
        bool isTargetPhaseFinished = false;

        for (std::vector<Player>::iterator it = player.begin(); it != player.end(); ++it)
        {
            if (isTargetPhaseFinished) 
            {
                break;
            }
            else if (it->GetIsDead()) {
                continue;
            }
            
            // 현황판 출력
            // Player의 XX스킬 공격 대상 설정
            // 몬스터 리스트 중에서 번호로 입력받기
        }               
                  
        // Enemy Turn
                

        // End Loop Condition Check;
        
        // 플레이어 파티의 생존 여부 체크
    }
    
    return false;
}

void BattleManager::AddRerollCount(int count)
{
    RerollCount += count;
    if (RerollCount < 0) 
    {
        RerollCount = 0;
    }
}

BattleManager::BattleManager() 
{
    RerollCount = 2;
}
