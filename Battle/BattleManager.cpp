#include <sstream>
#include "BattleManager.h"

bool BattleManager::Battle(std::vector<Player>& players, int stage)
{
    // 몬스터 생성
    std::vector<Monster> monsters = MonsterSpawn::getInstance().StageSpawner(stage);
    
    int turn = 1;

    stringstream ss;

    // TODO:: 배틀 시작할 때  줄바꿈함.
    std::cout << std::endl;
    std::cout << std::endl;

    ss << monsters.size() << "마리의 적이 시비를 걸어왔다." << std::endl;

    UIManager::getInstance().PrintMessage(ss.str());

    int userInput;

    while (true) 
    {
        UIManager::getInstance().GetUserInputForWait("");
        UIManager::getInstance().ClearMainWindowBox();


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
                    size_t endRange = aliveCharacters.size() > 0 ? aliveCharacters.size() - 1 : 0;
                    uniform_int_distribution<size_t> distance(0, endRange);
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
                    size_t endRange = aliveMonsters.size() > 0 ? aliveMonsters.size() - 1 : 0;
                    uniform_int_distribution<size_t> distance(0, endRange);
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

        std::stringstream turnSS;
        turnSS << "[ 턴 : " << turn << " ]";

        UIManager::getInstance().PrintMessage(turnSS.str());
        UIManager::getInstance().PrintBattleBoard(players, monsters);

        int remainRerollCount = RerollCount;

        // Player Turn
        // DICE PHASE

        // 주사위 굴리기 + 전황 출력
        RollDiceByPlayersAndPrintStatus(players, monsters);

        bool isDicePhaseFinished = false;
        std::vector<std::string> dicePhaseMenu = { "무엇을 하시겠습니까?", "", "0. 현황판 확인", "1. 액션 해제하기", "2. 리롤 하기", "3. 전부 리롤하기", "4. 아이템 사용", "5. 다음 페이즈로"};

        while (!isDicePhaseFinished)
        {

            if (remainRerollCount <= 0) 
            {
                break;
            }

            UIManager::getInstance().ClearMainWindowBox();
            UIManager::getInstance().PrintMessage(turnSS.str());
            UIManager::getInstance().PrintBattleBoard(players, monsters);


            std::stringstream ss;
            ss << "현재 남은 리롤 횟수 : " << remainRerollCount;
            UIManager::getInstance().PrintMessage(ss.str());

            UIManager::getInstance().PrintMenuBox(dicePhaseMenu);

            userInput = UIManager::getInstance().GetUserInputNumber("");

            switch (userInput) 
            {
            case 0:
                break;
            case 1:
            {
                // 주사위 리셋할 수 있게 처리
                std::vector<std::string> removeActionMenu = { "해제 할 액션 선택", "", "0. 뒤로가기" };
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

                UIManager::getInstance().PrintMenuBox(removeActionMenu);
                userInput = UIManager::getInstance().GetUserInputNumber("");
                if (userInput == 0)
                {
                    break;
                }

                if (menuIndexToPlayerMap.find(userInput) != menuIndexToPlayerMap.end())
                {
                    menuIndexToPlayerMap[userInput]->SetCurrentAction(nullptr);
                }
                else
                {
                    UIManager::getInstance().PrintInputWarning("유효하지 않은 명령입니다.");                    
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
                    UIManager::getInstance().PrintMessage("리롤 할 대상이 없습니다. 먼저 행동을 해제해 주세요.");
                    break;
                }


                --remainRerollCount;

                UIManager::getInstance().ClearMenuBox();

                // 주사위 새로 굴리기 -> 주사위 설정 안한 사람만
                RollDiceByPlayers(players);
            }
                break;
            case 3:
                for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
                {
                    it->SetCurrentAction(nullptr);
                }
                UIManager::getInstance().ClearMenuBox();

                --remainRerollCount;
                RollDiceByPlayers(players);
                break;

            case 4:
            {
                InventoryManager::getInstance().ShowInventory();

                std::vector<std::string> askchooseItemMenu = { "아이템을 사용하시겠습니까?", "", "0. 아이템 사용 취소", "", "[ 사용 하려는 아이템의 번호를 입력해주세요. ]" };
                UIManager::getInstance().PrintMenuBox(askchooseItemMenu);

                int itemNumber = 0;

                while (true)
                {
                    itemNumber = UIManager::getInstance().GetUserInputNumber("");

                    if (itemNumber == 0 || InventoryManager::getInstance().IsValidIndex(itemNumber - 1))
                    {
                        break;
                    }

                    UIManager::getInstance().PrintInputWarning("유효하지 않은 아이템입니다. 올바른 번호를 입력해주세요.");                   
                }

                UIManager::getInstance().ClearMenuBox();

                // 아이템 사용에서 빠져나감
                if (itemNumber == 0)
                {
                    break;
                }

                std::vector<std::string> askchoosePlayerMenu = { "아이템을 사용할 플레이어를 입력해주세요.", "", "0. 아이템 사용 취소"};
                std::stringstream ss;
                int menuIndex = 1;
                int playerNumber = 0;

                for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
                {
                    stringstream ss;
                    if (it->GetCurrentAction() != nullptr)
                    {
                        ss << menuIndex << ". " << it->GetName();
                        askchoosePlayerMenu.push_back(ss.str());
                        ++menuIndex;
                    }
                }

                UIManager::getInstance().PrintMenuBox(askchoosePlayerMenu);

                while (true)
                {
                    playerNumber = UIManager::getInstance().GetUserInputNumber("");
                    if (playerNumber == 0)
                    {
                        break;
                    }

                    if (playerNumber >= 1 && playerNumber <= players.size())
                    {
                        break;
                    }

                    UIManager::getInstance().PrintInputWarning("유효하지 않은 명령입니다.");
                }

                if (itemNumber != 0 && playerNumber > 0)
                {
                    InventoryManager::getInstance().Use(itemNumber - 1, &players[playerNumber - 1]);
                }

            }

                break;

            case 5:
                isDicePhaseFinished = true;
                break;

            default:
                UIManager::getInstance().PrintInputWarning("유효하지 않은 명령입니다.");
                break;
            }
        }

        UIManager::getInstance().ClearMenuBox();
        UIManager::getInstance().ClearMainWindowBox();       

        // TARGET PHASE        
        UIManager::getInstance().PrintMessage(turnSS.str());
        UIManager::getInstance().PrintBattleBoard(players, monsters);
        UIManager::getInstance().PrintMessage("* 주사위 결과를 적용할 대상을 선택하자. *");
        UIManager::getInstance().GetUserInputForWait("");
        UIManager::getInstance().ClearMainWindowBox();


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

            UIManager::getInstance().ClearMainWindowBox();


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

            UIManager::getInstance().PrintMessage(turnSS.str());
            UIManager::getInstance().PrintBattleBoard(players, monsters);

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
            


            // 메뉴 인덱스가 0이면 몬스터가 전부 죽었다는 뜻이므로 플레이어 타겟 페이지를 종료시킴
            if (menuIndex == 0)
            {
                isTargetPhaseFinished = true;
                continue;
            }

            UIManager::getInstance().PrintMenuBox(actionTargetMenu);
            userInput = UIManager::getInstance().GetUserInputNumber("");
            bool isValidOrder = false;


            while (!isValidOrder)
            {
                if (menuIndexToTargetMap.find(userInput) != menuIndexToTargetMap.end())
                {
                    Action* currentAction = it->GetCurrentAction();

                    it->DoAction({ menuIndexToTargetMap.find(userInput)->second });
                    currentAction->DoActive();
                    //it->DoActive();

                    isValidOrder = true;
                    continue;
                }

                UIManager::getInstance().PrintInputWarning("유효하지 않은 대상입니다.");
                userInput = UIManager::getInstance().GetUserInputNumber("");
            }
        }               

        UIManager::getInstance().ClearMainWindowBox();
        UIManager::getInstance().ClearMenuBox();

        UIManager::getInstance().PrintMessage(turnSS.str());
        UIManager::getInstance().PrintBattleBoard(players, monsters);


        // 넘어가기 적들 다 쓰러트리면 적 페이즈 X

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

        UIManager::getInstance().PrintMessage("* 조심해! 적들이 움직인다 *");
        UIManager::getInstance().GetUserInputForWait("");

        // Enemy Turn
        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        {
            if (it->GetIsDead())
            {
                continue;
            }

            UIManager::getInstance().ClearMainWindowBox();
            it->GetCurrentAction()->DoActive();
            //it->DoActive();
            UIManager::getInstance().PrintMessage(turnSS.str());
            UIManager::getInstance().PrintBattleBoard(players, monsters);
        }



        // TURN 엔드 처리 (상태이상 등)
        for (std::vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
        {
            it->EndTurn();
        }


        for (std::vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        {
            it->EndTurn();
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

        isWin = true;

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

void BattleManager::RollDiceByPlayersAndPrintStatus(std::vector<Player>& players, std::vector<Monster>& monsters)
{
    RollDiceByPlayers(players);
    UIManager::getInstance().PrintBattleBoard(players, monsters);
}


void BattleManager::RollDiceByPlayers(std::vector<Player>& player)
{

    UIManager::getInstance().PrintMessage("주사위를 굴리자");
    UIManager::getInstance().GetUserInputForWait("");

    for (std::vector<Player>::iterator it = player.begin(); it != player.end(); ++it)
    {
        if (it->GetCurrentAction() == nullptr)
        {
            it->RollDice();
            // 주사위 대상 초기화
            std::vector<Character*> none;
            it->GetCurrentAction()->DoAction(none, none);
        }        
    }    
    UIManager::getInstance().ClearMainWindowBox();    
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
