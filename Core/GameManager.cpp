#include "GameManager.h"


using namespace std;

void GameManager::InitializeCharacter(vector<Player>& Players)
{
    UIManager& UM = UIManager::getInstance();
    InventoryManager& IM = InventoryManager::getInstance();

    int PlayerCount = 0;
    string Name;

    //플레이어 이름 및 직업 정하기
    for (int i = 0; i < 3; ++i)
    {
        int jobChoice;

        
        Name = UM.GetUserInput(to_string(i+1) + "번 플레이어 이름을 입력해주세요: ");

        //0~3사이의 값이 안들어오는거 방지
        while (true)
        {
            UM.ClearMainWindowBox();
            UM.PrintMessage("직업 선택 (1:Fighter, 2:Archer, 3:Defender, 4:Rogue)");         
            jobChoice = UM.GetUserInputNumber(to_string(i + 1) + "번 플레이어의 직업을 정해주세요: ");
            if (jobChoice >= 1 && jobChoice <= 4)
            {
                break;
            }
            else
            {
                UM.PrintInputWarning("1~4자리 숫자를 입력해주세요.");
            }
        }


        auto& TM = TemplateManager::getInstance();
     
        JobType ChoicedJob = static_cast<JobType>(jobChoice-1);

        Dice dice = TemplateManager::getInstance().GetDiceByType(ChoicedJob);

        // 입력받은 숫자를 JobType으로 변환하여 추가
        Players.push_back(Player(10, dice, Name, ChoicedJob));
    }

    UM.ClearMainWindowBox();

    // 인벤토리에 힐링 포션 하나 넣기
    Item* hpPotion = new HealingPotion();
    IM.AddItem(hpPotion);
}

void GameManager::GameStart()
{

    BattleManager& BM = BattleManager::getInstance();
    ShopManager& SM = ShopManager::getInstance();
    UIManager& UM = UIManager::getInstance();
    InventoryManager& IM = InventoryManager::getInstance();

    //플레이어 캐릭터 초기화
    InitializeCharacter(Players);

    //초기화 정상작동 확인
    for (int i=0; i<Players.size(); ++i)
    {
        UM.PrintMessage(to_string(i+1) + " 번째 플레이어 이름: " + Players[i].GetName() + " 직업: " + GetJobName(Players[i].GetJobType()));
    }
    //IM.ShowInventory();

    SM.EnterShop(Players, PlayerMoney);
    //주사위 확인 혹은 전투 시작 선택지
    //전투 시작 선택지 입력 전까지 반복
    while (true)
    {
        vector<string> menu = { "1. 플레이어 직업 주사위 확인", "2. 전투 시작" };
        UM.PrintMenuBox(menu);

        int PlayerChoice = UM.GetUserInputNumber("선택 입력: ");

        //플레이어의 이름을 통해 주사위 보여줌
        if (PlayerChoice == 1)
        {
            PrintPlayerDice();
            continue;
        }
        //전투 돌입을 위해 while 탈출
        else if (PlayerChoice == 2)
        {
            break;
        }
    }


    UM.ClearMenuBox();
    //처음 스테이지 초기화
    CurrentStage = 1;

    cout << "\"숲 속의 던전은 고요하고, 가끔씩 새소리만 들려옵니다.\"" << endl;
    cout << "\"던전 안쪽으로 좀 더 들어가자,순찰 중인 듯한 고블린과 마주칩니다.\"" << endl;
    cout << "\"고블린은 간만에 먹잇감을 발견했다는 듯, 망설임없이 달려듭니다.\"" << endl;

    //스테이지가 3이 되기전까지 전투 반복
    while (CurrentStage != 5)
    {

        //전투 돌입
        GameResult = BattleResult(BM.Battle(Players, CurrentStage));

        //배틀 결과에 따라 전멸 시 즉시 게임 죵로
        if (GameResult == true)
        {
            //게임 종료 후 스테이지 증가
            PrintStoryClear(CurrentStage);
            ++CurrentStage;

        }
        else
        {
            break;
        }
        if (CurrentStage == 4)
        {
            SM.EnterShop(Players, PlayerMoney);
        }


    }

    //게임 종료
    return;

}

// 전투 결과에 따라 게임 종료 혹은 경험치&아이템 획득
bool GameManager::BattleResult(bool Result)
{
    UIManager& UM = UIManager::getInstance();

    if (Result == true)
    {
        // 경험치 획득
        for (Player& player : Players)
        {
            if (player.GetIsDead() == false)
            {
                player.SetExp(player.GetExp() + 10);
                
            }
        }
        // 돈 획득
        PlayerMoney += 100;

        UM.ClearMainWindowBox();
        cout << "보상으로 모든 플레이어는 각각 10의 경험치와 100골드를 획득했습니다." << endl;
        cout << endl;
        for (Player player : Players)
        {
            cout << player.GetName() << "의 경험치: " << player.GetExp() << "/" << player.GetNextLevelExp() << endl;
        }
        cout << "현재 보유 골드: " << PlayerMoney << endl;
        return true;
    }
    else
    {
        // 플레이어 캐릭터 전멸 게임 종료
        cout << "모든 캐릭터 사망하였습니다. 게임 종료" << endl;
        return false;
    }
}


// 모든 Player의 직업 다이스 출력
void GameManager::PrintPlayerDice()
{
    UIManager& UM = UIManager::getInstance();
    int PlayerChoice;
    int TotalPlayer = Players.size();
    int CurrentPlayer = 0;
    vector<string> menu;

    
    while (CurrentPlayer >= 0 && CurrentPlayer < TotalPlayer)
    {
        UM.ClearMainWindowBox();
        UM.PrintMessage(to_string(CurrentPlayer+1) + " 번째 플레이어 이름: " + Players[CurrentPlayer].GetName() + " 직업: " + GetJobName(Players[CurrentPlayer].GetJobType()));
        Players[CurrentPlayer].GetDice().PrintActionInfo();

        //현재 플레이어 수에 따라 선택 메뉴 출력
        if (CurrentPlayer == 0)
        {
            menu = { "1. 다음 주사위", "0. 나가기" };
        }
        else if (CurrentPlayer == Players.size()-1)
        {
            menu = { "1. 이전 주사위", "0. 나가기" };
        }
        else
        {
            menu = { "1. 이전 주사위", "2. 다음 주사위", "0. 나가기" };

        }

        UM.ClearMenuBox();
        UM.PrintMenuBox(menu);
        PlayerChoice = UM.GetUserInputNumber("선택 입력: ");
        if (PlayerChoice == 0)
        {
            break;
        }
        else if (PlayerChoice == 1)
        {
            if (CurrentPlayer == 0)
            {
                CurrentPlayer += 1;
            }
            else
            {
                CurrentPlayer -= 1;
            }
            
        }
        else if (PlayerChoice == 2)
        {
            CurrentPlayer += 1;
        }
    }

    UM.ClearMainWindowBox();
}



//Player의 인덱스를 이름으로 반환
//찾지못하면 -1 반환
int GameManager::GetPlayerByName()
{
    string PlayerInput;
    int PlayerIndex = -1;
    while (true)
    {
        cout << "선택 입력 : ";
        cin >> PlayerInput;
        if (cin.fail())
        {
            cout << "잘못된 입력입니다. 문자를 입력해주세요." << endl;
        }
        else
        {
            for (int i=0; i<Players.size(); ++i)
            {
                if (Players[i].GetName() == PlayerInput)
                {
                    PlayerIndex = i;                   
                }
            }
        }
        break;

    }
    return PlayerIndex;
}

string GameManager::GetJobName(JobType JobType)
{
    switch (JobType)
    {
    case JobType::Archer:
        return "Archer";
        break;
    case JobType::Fighter:
        return "Fighter";
        break;
    case JobType::Rogue:
        return "Rogue";
        break;
    case JobType::Defender:
        return "Defender";
        break;
    }
  }


void GameManager::PrintStoryClear(int CurrentStage)
{
    switch (CurrentStage)
    {
    case 1:
        cout << endl;
        cout << "\"더 깊숙이 들어갔지만, 입구에서도 느낀 것처럼 던전은 마물이 산다는 것을 믿기 힘들 정도로 평화로워 보입니다.\"" << endl;
        cout << "\"하지만 그런 생각도 잠시, 어디선가 소리없이 나타난 늑대와 고블린에게 파티는 포위되었습니다.\"" << endl;
        break;
    case 2:
        cout << endl;
        cout << "\"주변은 빽빽한 나무들로 인해 상당히 어둡습니다.\"" << endl;
        cout << "\"뿌리가 우거진 땅을 간신히 넘어서 나아가니, 앞에 희미한 불빛이 보입니다.\"" << endl;
        cout << "\"당신의 파티는 조심스럽게 다가갑니다.\"" << endl;
        cout << "\"그것은 오크가 피운 모닥불이었고, 오크 자신의 휴식을 방해한 자들을 용서할 기색이 없습니다.\"" << endl;
        break;
    case 3:
        cout << endl;
        cout << "\"오크를 쓰러뜨리고 던전의 최심부로 들어가자, 쿵, 하는 위압적인 소리가 들려옵니다.\"" << endl;
        cout << "\"당신의 파티는 갑자기 들려온 소리에 긴장하며 청각을 곤두세웁니다.\"" << endl;
        cout << "\"나무 사이로 거대한 그림자가 비치는가 싶더니, 금세 트롤이 모습을 나타냅니다.\"" << endl;
        cout << "\"트롤은 자신의 몸집에 어울리는 나무 한 그루만한 몽둥이를 들고, 조그만 인간 따위는 파리나 다름없다는 듯 휘둘러대기 시작합니다.\"" << endl;
        cout << "\"이 트롤이 바로 던전의 주인입니다. 당신의 파티는 전투 준비를 합니다.\"" << endl;
        break;
    case 4:
        cout << endl;
        cout << "\"생각보다 위압적인 상대는 아니었지만, 운이 따르지 않았다면 죽을 수도 있었습니다.\"" << endl;
        cout << "\"안도의 한숨을 내쉬며, 당신의 파티는 다친 몸을 이끌고 마을로 돌아갑니다.\"" << endl;
        break;
    default:
        break;
    }
}

