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

static void PrintMenu(const std::vector<std::string>& menus, int width = 100) 
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

static void PrintBattleBoard(vector<Player>& player, vector<Monster>& monster, std::map<Monster*, std::vector<Player*>> targetMap)
{
    std::string line(100, '=');
    std::cout << line << std::endl;
    std::cout << "현황판" << std::endl;
    std::cout << line << std::endl;
    for (vector<Player>::iterator it = player.begin(); it != player.end(); ++it)
    {
        std::cout << it->GetName() << "  " << it->GetHP() << " / " << it->GetMaxHP();

        // 장착상태 확인
        if (it->GetCurrentAction() != nullptr)
        {
            std::cout << " " << it->GetCurrentAction()->GetActionName();                
        }
        
        std::cout << std::endl;

    }
    std::cout << std::endl;    
    for (vector<Monster>::iterator it = monster.begin(); it != monster.end(); ++it)
    {
        std::cout << it->GetName() << "  " << it->GetHP() << " / " << it->GetMaxHP();

        Action* currentAction = it->GetCurrentAction();
        if (currentAction != nullptr) {
            std::cout << " " << currentAction->GetActionName();

            // Target 설정
            if (targetMap.find(&(*it)) != targetMap.end()) {
                auto targetPlayers = targetMap.at(&(*it));
                std::cout << "    | ";
                for (auto it = targetPlayers.begin(); it != targetPlayers.end(); ++it) {
                    std::cout << (*it)->GetName() << " | ";
                }
            }
        }

        std::cout << std::endl;
    }
    std::cout << line << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

static void PrintPlayerActionBoard(vector<Player>& players)
{
    std::string line(100, '=');
    std::cout << line << std::endl;
    std::cout << "액션 현황판" << std::endl;
    std::cout << line << std::endl;
    for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
    {
        std::cout << it->GetName() << "  ";

        // 장착상태 확인
        if (it->GetCurrentAction() != nullptr)
        {
            std::cout << " " << it->GetCurrentAction()->GetActionName();
        }

        std::cout << std::endl;

    }
    std::cout << line << std::endl;
    std::cout << std::endl;
}

#pragma endregion

bool BattleManager::Battle(std::vector<Player>& players, int stage)
{
    // 몬스터 생성
    std::vector<Monster> monsters;
    monsters.reserve(6);
    
    for (int i = 0; i < 3; ++i) {
        Monster monster = TemplateManager::getInstance().GetMonsterByGoblin();
        monster.SetCurrentAction(nullptr);
        monsters.push_back(monster);
    }

    std::map<Monster*, std::vector<Player*>> targetMap;

    int turn = 1;

    while (true) 
    {
        // 플레이어 다이스 상태 초기화
        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {
            it->SetCurrentAction(nullptr);
        }

        // Enemy 
            // Enemy 다이스를 굴림 -> 다이스는 단일
            // 사용은 X, 공격 대상만 보여줌

        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it) 
        {
            // 몬스터의 기존 타겟 초기화
            targetMap[&(*it)].clear();

            // 몬스터가 주사위를 굴림
            it->RollDice();            


            // 생존자 리스트 중에 한명을 임의의 타겟으로 설정
            std::vector<Player*> alivePlayers;
            for (Player& p : players)
            {
                if (p.GetHP() > 0) { // HP가 0보다 큰 생존자만 추가
                    alivePlayers.push_back(&p);
                }
            }

            if (!alivePlayers.empty())
            {

                std::random_device rd;
                std::mt19937 g(rd());

                // 범위 지정
                uniform_int_distribution<int> distance(0, alivePlayers.size() - 1);


                targetMap[&(*it)].push_back(alivePlayers[distance(g)]);
            }
        }

        PrintBattleBoard(players, monsters, targetMap);

        int remainRerollCount = RerollCount;

        std::stringstream ss;
        ss << "[ 턴 : " << turn << " ]";
        PrintMessage(ss.str());

        // Player Turn
        // DICE PHASE

        // 주사위 굴리기
        RollDiceByPlayers(players);

        bool isDicePhaseFinished = false;
        std::vector<std::string> dicePhaseMenu = { "플레이어 행동", "", "0. 현황판 확인", "1. 액션 해제하기", "2. 리롤하기", "3. 다음 페이즈로" };              

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
                PrintBattleBoard(players, monsters, targetMap);
                break;
            case 1:
            {
                // 주사위 리셋할 수 있게 처리
                std::vector<std::string> removeActionMenu = { "해제 할 액션 선택", "" };
                std::map<int, Player*> menuIndexToPlayerMap;
                int menuIndex = 1;

                for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
                {
                    if (it->GetIsDead())
                    {
                        continue;
                    }

                    stringstream ss;
                    if (it->GetCurrentAction() != nullptr) {
                        ss << menuIndex << ". " << it->GetName() << " 의 액션 " << it->GetCurrentAction()->GetActionName() << " 해제";
                    }
                    removeActionMenu.push_back(ss.str());
                    menuIndexToPlayerMap[menuIndex] = &(*it);
                    ++menuIndex;
                }

                PrintMenu(removeActionMenu, 80);
                int playerChoice = GetUserInputNum();
                if (menuIndexToPlayerMap.find(playerChoice) != menuIndexToPlayerMap.end())
                {
                    menuIndexToPlayerMap[playerChoice]->SetCurrentAction(nullptr);
                    PrintPlayerActionBoard(players);
                }
                else
                {
                    cout << "유효하지 않은 명령입니다.";
                }
            }

                break;
            case 2:
            {
                // 플레이어 모두가 액션이 정해진 상태라면 리롤 없이 해제 요청
                bool allPlayerReadyAction = true;
                for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
                {
                    if (!it->GetIsDead() && it->GetCurrentAction() == nullptr)
                    {
                        allPlayerReadyAction = false;
                        break;
                    }
                }

                if (allPlayerReadyAction)
                {
                    PrintMessage("리롤 할 대상이 없습니다. 먼저 행동을 해제해 주세요.");
                    break;
                }


                --remainRerollCount;

                // 주사위 새로 굴리기 -> 주사위 설정 안한 사람만
                RollDiceByPlayers(players);
            }
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

        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {
            if (isTargetPhaseFinished) 
            {
                break;
            }
            else if (it->GetIsDead())
            {
                continue;
            }
            
            // 현황판 출력
            // Player의 XX스킬 공격 대상 설정
            // 몬스터 리스트 중에서 번호로 입력받기
        }               
                  
        // Enemy Turn
        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        {
            if (it->GetIsDead())
            {
                continue;
            }

            std::vector<Character*> characters;
            characters.reserve(20);

            // 몬스터가 주사위를 굴림
            auto targets = targetMap.find(&(*it));
            if (targets != targetMap.end())
            {
                for (auto& p : targets->second)
                {
                    // 3. Player는 Character를 상속받았으므로 주소값을 push_back 가능
                    characters.push_back(p);
                }
            }
            
            it->DoAction(characters);            

            // TODO:: 랜덤으로 초기화 + 타겟이 없는 경우는???             
        }


        // End Loop Condition Check;

        // 플레이어 파티의 생존 여부 체크
        bool isGameOver = true;
        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {
            if (it->GetIsDead())
            {
                isGameOver = false;
                break;
            }
        }

        if (isGameOver)
        {
            // TODO:: 디버깅 확인용 GameManager에서 처리되면 삭제
            std::cout << " 전투에서 패배했습니다." << std::endl;
            return false;
        }

        bool isWin = true;

        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        {
            if (it->GetIsDead())
            {
                isWin = false;
                break;
            }
        }

        if (isWin)
        {
            return true;
        }
        
        ++turn;
    }
    
    return false;
}

void BattleManager::RollDiceByPlayers(std::vector<Player>& player)
{

    WaitForEnter("주사위를 굴립니다. ( 계속 하려면 엔터키를 눌러주세요. )");

    for (std::vector<Player>::iterator it = player.begin(); it != player.end(); ++it)
    {
        if (it->GetCurrentAction() == nullptr)
        {
            it->RollDice();
        }        
    }    

    PrintPlayerActionBoard(player);
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
