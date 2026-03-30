#include "GameManager.h"


using namespace std;

void GameManager::InitializeCharacter(vector<Player>& Players)
{
    int PlayerCount = 0;
    string Name;

    for (int i = 0; i < 3; ++i)
    {
        int jobChoice;

        cout << i + 1 << "번 플레이어 이름: ";
        getline(cin, Name);

        //0~3사이의 값이 안들어오는거 방지
        while (true)
        {
            cout << "직업 선택 (1:Warrior, 2:Archer, 3:Defender, 4:Rogue): ";
            if (!(cin >> jobChoice))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "숫자만 입력 가능합니다. 다시 입력해주세요" << endl;
                continue;
            }

            cin.ignore();

            if (jobChoice >= 1 && jobChoice <= 4)
            {
                break;
            }
            else
            {
                cout << "1~4 사이의 숫자를 입력해주세요" << endl;
            }
        }


        auto& TM = TemplateManager::getInstance();
     
        JobType ChoicedJob = static_cast<JobType>(jobChoice-1);

        Dice dice = TemplateManager::getInstance().GetDiceByType(ChoicedJob);

        // 입력받은 숫자를 JobType으로 변환하여 추가
        Players.push_back(Player(10, dice, Name, ChoicedJob));
    }

    InventoryManager& IM = InventoryManager::getInstance();
    Item* hpPotion = new HealingPotion();
    IM.AddItem(hpPotion);
    IM.ShowInventory();
}

void GameManager::GameStart()
{

    BattleManager& BM = BattleManager::getInstance();
    ShopManager& SM = ShopManager::getInstance();

    //플레이어 캐릭터 초기화
    InitializeCharacter(Players);
    //초기화 정상작동 확인
    cout << "첫 번째 플레이어 이름: " << Players[0].GetName() << " 직업: " << static_cast<int>(Players[0].GetJobType())+1 << endl;
    cout << "두 번째 플레이어 이름: " << Players[1].GetName() << " 직업: " << static_cast<int>(Players[1].GetJobType())+1 << endl;

    SM.EnterShop(Players, PlayerMoney);
    //주사위 확인 혹은 전투 시작 선택지
    //전투 시작 선택지 입력 전까지 반복
    while (true)
    {
        cout << "=================================" << endl;
        cout << "1. 플레이어 직업 주사위 확인" << endl;
        cout << "2. 전투 시작" << endl;
        int PlayerChoice = GetUserInputNum();

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

    //처음 스테이지 초기화
    CurrentStage = 1;
    //스테이지가 3이 되기전까지 전투 반복
    while (CurrentStage != 3)
    {

        //전투 돌입
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


    }

    //상점 진입
    //SM.EnterShop(Players, PlayerMoney);

    //게임 종료
    return;

    //전투 결과에 따라
    BattleResult(BM.Battle(Players, CurrentStage));

}

// 전투 결과에 따라 게임 종료 혹은 경험치&아이템 획득
bool GameManager::BattleResult(bool Result)
{
    if (Result == true)
    {
        // 경험치 획득
        for (Player& player : Players)
        {
            if (player.GetIsDead() != false)
            {
                player.SetExp(player.GetExp() + 10);
            }
        }
        // 돈 획득
        PlayerMoney += 100;
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
    for (Player player : Players)
    {
        player.GetDice().PrintActionInfo();
    }
    
}


// 유저 입력 받은 후 입력값 반환
int GameManager::GetUserInputNum()
{
    int PlayerInput;
    while (true)
    {
        cout << "선택 입력 : ";
        cin >> PlayerInput;
        if (cin.fail())
        {
            cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
            continue;

        }
        else
        {
            break;
        }
    }
    return PlayerInput;
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

