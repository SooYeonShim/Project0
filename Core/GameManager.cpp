#include "GameManager.h"


using namespace std;


//캐릭터 생성
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
            UM.PrintMessage("직업 선택 (1:Fighter, 2:Archer, 3:Defender, 4:Rogue, 5:Cleric)");         
            jobChoice = UM.GetUserInputNumber(to_string(i + 1) + "번 플레이어의 직업을 정해주세요: ");
            if (jobChoice >= 1 && jobChoice <= 5)
            {
                break;
            }
            else
            {
                UM.PrintInputWarning("1~5 사이 숫자를 입력해주세요.");
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

    UM.ClearMenuBox();

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

    //스테이지가 3이 되기전까지 전투 반복
    while (CurrentStage != 5)
    {

        //전투 돌입
        UM.ClearMenuBox();
        GameResult = BattleResult(BM.Battle(Players, CurrentStage));

        //배틀 결과에 따라 전멸 시 즉시 게임 죵로
        if (GameResult == true)
        {
            //게임 종료 후 스테이지 증가
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

        //현재 출력 중인 플레이어 번호에 따라 선택 메뉴 다르게 출력
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

//직업 타입을 string으로 출력
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



