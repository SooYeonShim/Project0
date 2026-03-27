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

static void PrintBattleBoard(vector<Player>& player, vector<Monster>& monster)
{
    std::string line(100, '=');
    std::cout << line << std::endl;
    std::cout << "현황판" << std::endl;
    std::cout << line << std::endl;
    for (vector<Player>::iterator it = player.begin(); it != player.end(); ++it)
    {
        std::cout << it->GetName() << "  ";

        if (!it->GetIsDead()) {

            std::cout << it->GetHP() << " / " << it->GetMaxHP();

            // 장착상태 확인
            if (it->GetCurrentAction() != nullptr)
            {
                std::cout << " " << it->GetCurrentAction()->GetActionName();
            }


        }
        else
        {
            std::cout << "[ 사망 ]";
        }

        std::cout << std::endl;

    }
    std::cout << std::endl;    

    for (vector<Monster>::iterator it = monster.begin(); it != monster.end(); ++it)
    {
        std::cout << it->GetName() << "  ";

        if (!it->GetIsDead()) {
            std::cout << it->GetHP() << " / " << it->GetMaxHP();

            Action* currentAction = it->GetCurrentAction();
            if (currentAction != nullptr) {
                std::cout << " " << currentAction->GetActionName();
                
                std::vector<Character*> targets = currentAction->GetTatgerCharacters();

                std::cout << "    | ";

                // 적군 지정된 경우 출력 (공격 등)
                if (!currentAction->GetTatgerCharacters().empty()) {
                    for (std::vector<Character*>::iterator it = targets.begin(); it != targets.end(); ++it) {
                        std::cout << (*it)->GetName() << " | ";
                    }
                }
            }
        }
        else
        {
            std::cout << "[ 사망 ]";
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
        if (it->GetIsDead())
        {
            std::cout << " [ 사망 ]";
        }
        else if (it->GetCurrentAction() != nullptr)
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
    std::vector<Monster> monsters = MonsterSpawn::getInstance().StageSpawner(stage);
    
    int turn = 1;

    while (true) 
    {
        // 플레이어 다이스 상태 초기화
        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {
            it->SetCurrentAction(nullptr);
        }

        // Enemy 
        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it) 
        {
            // 몬스터의 기존 타겟 초기화

            // 몬스터가 주사위를 굴림
            it->RollDice();

            std::vector<Character*> aliveCharacters;

            TargetType type = it->GetCurrentAction()->GetTargetType();

            switch (type)
            {
            case TargetType::ENEMY:
            {
                for (Player& p : players)
                {
                    if (!p.GetIsDead()) { // HP가 0보다 큰 생존자만 추가
                        aliveCharacters.push_back(&p);
                    }
                }

                if (!aliveCharacters.empty())
                {
                    std::random_device rd;
                    std::mt19937 g(rd());

                    // 범위 지정
                    uniform_int_distribution<int> distance(0, aliveCharacters.size() - 1);
                    it->DoAction({ aliveCharacters[distance(g)] });
                }
            }
                break;
            case TargetType::FRIENDLY:
            {
                std::vector<Character*> aliveMonsters;
                for (Monster& m : monsters)
                {
                    if (!m.GetIsDead())
                    {
                        aliveMonsters.push_back(&m);
                    }
                }

                if (!aliveMonsters.empty())
                {
                    std::random_device rd;
                    std::mt19937 g(rd());

                    // 범위 지정
                    uniform_int_distribution<int> distance(0, aliveMonsters.size() - 1);
                    it->DoAction({ aliveMonsters[distance(g)] });
                }
            }
                break;
            case TargetType::MYSELF:
                it->DoAction({ &(*it) });

                break;
            case TargetType::ENEMYALL:

                for (Player& p : players)
                {
                    if (!p.GetIsDead())
                    {
                        aliveCharacters.push_back(&p);
                    }
                }


                it->DoAction( aliveCharacters );
                break;
            case TargetType::FRIEDLYALL:

                for (Monster& p : monsters)
                {
                    if (!p.GetIsDead())
                    { 
                        aliveCharacters.push_back(&p);
                    }
                }

                it->DoAction( aliveCharacters );
            }

        }

        PrintBattleBoard(players, monsters);

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
                PrintBattleBoard(players, monsters);
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
            else if (it->GetCurrentAction() == nullptr)
            {
                continue;
            }

            Action* currentAction = it->GetCurrentAction();

            std::vector<Character*> aliveCharacters;

            // 적 전체 & 아군 전체인 경우 따로 물을 필요 X 바로 적용
            if (currentAction->GetTargetType() == TargetType::FRIEDLYALL)
            {
                for (Player& p : players)
                {
                    if (!p.GetIsDead())
                    {
                        aliveCharacters.push_back(&p);
                    }
                }

                it->DoAction(aliveCharacters);
                continue;
            }
            else if (currentAction->GetTargetType() == TargetType::ENEMYALL)
            {
                for (Monster& p : monsters)
                {
                    if (!p.GetIsDead())
                    {
                        aliveCharacters.push_back(&p);
                    }
                }

                it->DoAction(aliveCharacters);

                continue;
            }
            else if (currentAction->GetTargetType() == TargetType::MYSELF)
            {
                it->DoAction({ &(*it) });
                continue;
            }


            PrintBattleBoard(players, monsters);

            int menuIndex = 0;
            std::map<int, Character*> menuIndexToTargetMap;
            std::stringstream sst;
            sst << it->GetName() << " 의 " << it->GetCurrentAction()->GetActionName();

            std::vector<std::string> actionTargetMenu = { sst.str(), ""};

            // 몬스터 단일 대상
            if (currentAction->GetTargetType() == TargetType::ENEMY)
            {
                for (std::vector<Monster>::iterator mostser_it = monsters.begin(); mostser_it != monsters.end(); ++mostser_it)
                {
                    if (mostser_it->GetIsDead())
                    {
                        continue;
                    }

                    ++menuIndex;

                    stringstream ss;

                    if (mostser_it->GetCurrentAction() != nullptr)
                    {
                        ss << menuIndex << ". " << mostser_it->GetName();
                    }
                    actionTargetMenu.push_back(ss.str());
                    menuIndexToTargetMap[menuIndex] = &(*mostser_it);
                }
            }
            else if (currentAction->GetTargetType() == TargetType::FRIENDLY) // 아군 단일 대상
            {
                for (std::vector<Player>::iterator player_it = players.begin(); player_it != players.end(); ++player_it)
                {
                    if (player_it->GetIsDead())
                    {
                        continue;
                    }

                    ++menuIndex;

                    stringstream ss;

                    if (player_it->GetCurrentAction() != nullptr)
                    {
                        ss << menuIndex << ". " << player_it->GetName();
                    }
                    actionTargetMenu.push_back(ss.str());
                    menuIndexToTargetMap[menuIndex] = &(*player_it);
                }
            }
            


            // 메뉴 인덱스가 0이면 몬스터가 전부 죽었다는 뜻이므로 플레이어 타겟 페이즈를 종료시킴
            if (menuIndex == 0)
            {
                isTargetPhaseFinished = true;
                continue;
            }

            PrintMenu(actionTargetMenu);
            int userInput = GetUserInputNum();
            bool isValidOrder = false;


            while (!isValidOrder)
            {
                if (menuIndexToTargetMap.find(userInput) != menuIndexToTargetMap.end())
                {
                    Action* currentAction = it->GetCurrentAction();

                    it->DoAction({ menuIndexToTargetMap.find(userInput)->second });
                    currentAction->DoActive();

                    isValidOrder = true;
                    continue;
                }
                cout << "유효하지 않은 대상입니다." << std::endl;
                int userInput = GetUserInputNum();
            }



            PrintBattleBoard(players, monsters);
        }               
                  
        // Enemy Turn
        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        {
            if (it->GetIsDead())
            {
                continue;
            }
           
            it->GetCurrentAction()->DoActive();           
        }


        // End Loop Condition Check;

        // 플레이어 파티의 생존 여부 체크
        bool isGameOver = true;
        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {
            if (!it->GetIsDead())
            {
                isGameOver = false;
                break;
            }
        }

        if (isGameOver)
        {            
            return false;
        }

        bool isWin = true;

        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        {
            if (!it->GetIsDead())
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
