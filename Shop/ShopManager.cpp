#include "ShopManager.h"
#include "../Template/TemplateManager.h"
#include "GameManager.h"

// 살아있는 플레이어 체력 회복
void ShopManager::HealAllPlayer(vector<Player>& Players, int& PlayerMoney)
{
    UIManager& UM = UIManager::getInstance();

    if (PlayerMoney >= 50)
    {
        for (Player& player : Players)
        {
            //모든 플레이어의 체력 5 회복
            player.TakeHeal(5);
        }
        PlayerMoney -= 50;
        UM.PrintMessage("모든 파티원 체력 회복! -50 골드");
        cout << "보유 골드: " << PlayerMoney << endl;

    }
    else
    {
        UM.PrintInputWarning("보유한 돈이 부족합니다.");
    }

}

// 아이템 구매
void ShopManager::BuyItem(int& PlayerMoney)
{
    
    InventoryManager& IM = InventoryManager::getInstance();
    UIManager& UM = UIManager::getInstance();

    UM.ClearMenuBox();
    vector<string> Menu = { "구매하고 싶은 아이템을 선택해주세요.", "", "1. 힐링 포션" };
    UM.PrintMenuBox(Menu);


    int PlayerChoice = UM.GetUserInputNumber("선택 입력: ");
    
    switch (PlayerChoice)
    {
    // 힐링 포션 구매
    case 1:
        if (PlayerMoney >= 50)
        {
            Item* hpPotion = new HealingPotion();
            IM.AddItem(hpPotion);

            UM.ClearMainWindowBox();
            UM.PrintMessage("힐링 포션이 구매되었습니다. (-50 골드)");
            PlayerMoney -= 50;
            UM.PrintMessage("남은 돈: " + to_string(PlayerMoney));        
        }
        else
        {
            UM.PrintInputWarning("보유한 돈이 부족합니다.");
        }
        break;
    default:
        UM.PrintInputWarning("잘못된 아이템을 선택하셨습니다.");
        break;
    }
\
    

}

//상점 진입
void ShopManager::EnterShop(vector<Player>& Players, int& PlayerMoney)
{

    
    InventoryManager& IM = InventoryManager::getInstance();
    UIManager& UM = UIManager::getInstance();
    TemplateManager& TM = TemplateManager::getInstance();

    UM.ClearMainWindowBox();

    while (true)
    {
        int PlayerInput = 0;

        PrintShopUI(PlayerMoney);
        PlayerInput = UM.GetUserInputNumber("선택 입력: ");
        if (PlayerInput == 1)
        {
            UM.ClearMainWindowBox();
            HealAllPlayer(Players, PlayerMoney);
            break;
        }
        else if (PlayerInput == 2)
        {
            UM.ClearMainWindowBox();
            BuyItem(PlayerMoney);
            continue;

        }
        else if (PlayerInput == 3)
        {
            UM.ClearMainWindowBox();
            IM.ShowInventory();
            continue;
        }
        // 4. 다이스면 구입하기
        else if (PlayerInput == 4)
        {
            UM.ClearMainWindowBox();
            ShopActionUI(Players, PlayerMoney);
            UM.ClearMainWindowBox();
            continue;
        }
        else if (PlayerInput == 7)
        {
            CheatShop(Players);
            continue;
        }
        else if (PlayerInput == 8)
        {
            CheatShop2(Players);
            continue;
        }
        else if (PlayerInput == 0)
        {
            break;
        }
        else 
        {
            UM.PrintInputWarning("0~4자리 숫자를 입력해주세요.");
        }

    }
}


// 상점 UI 출력
void ShopManager::PrintShopUI(int PlayerMoney)
{
    UIManager& UM = UIManager::getInstance();

    UM.ClearMenuBox();

    vector<string> Menu;

    Menu = { "     ★  상점  ★", "파티원이 보유한 돈: " + to_string(PlayerMoney), "1. 휴식하기", "2. 아이템 구매", "3. 인벤토리 확인", "4. 다이스 면 구입하기","0. 상점 나가기" };
    UM.PrintMenuBox(Menu);
}

void ShopManager::ShopActionUI(vector<Player>& Players, int& PlayerMoney)
{
    GameManager& GM =  GameManager::getInstance();
    UIManager& UM = UIManager::getInstance();
    TemplateManager& TM = TemplateManager::getInstance();
    Action* FundAction = nullptr;
    bool brk = true;

    // 요구조건 = 50골드이상
    if (PlayerMoney < 50)
    {
        UM.PrintInputWarning("다이스 면을 사려면 50골드 이상이 필요합니다.");
        return;
    }

    // 1. 구입할 면 선택
    while (brk)
    {
        // 메모리릭방지를 위한 delete
        if (FundAction != nullptr)
            delete FundAction;
        FundAction = nullptr;

        // 면 리스트 출력
        TM.PrintShopActionList();

        // 선택지
        UM.ClearMenuBox();
        vector<string> Menu = { "구매하고 싶은 면을 선택해주세요. 가격은 50골드입니다.", "0. 돌아가기"};
        UM.PrintMenuBox(Menu);

        int num = UM.GetUserInputNumber("선택 입력: ");

        // 돌아가는 버튼 입력 시
        if (num == 0)
            break;

        // 선택지에 맞는 면 찾기
        Action* FundAction = TM.CreateActionByShopIndex(num - 1);
        if (FundAction == nullptr)
        {
            UM.PrintInputWarning("잘못된 아이템을 선택하셨습니다.");
            continue;
        }


        // 2. 장착할 플레이어 선택. 서브) 플레이어 정보보기
        while (true)
        {
            // 선택지
            UM.ClearMenuBox();
            UM.ClearMainWindowBox();
            Menu = { "장착할 파티원을 선택하세요.", "0. 돌아가기", "99. 파티원 다이스 정보 자세히 보기"};
            UM.PrintMenuBox(Menu);

            // 메인윈도우 창에 플레이어 다이스정보 간략 출력
            for (int i = 0; i < Players.size(); ++i)
            {
                cout << i+1 << "번 파티원 [" << Players[i].GetName() << "]" << endl;
                Players[i].GetDice().PrintActionSmallInfo();
            }

            num = UM.GetUserInputNumber("파티원 번호 입력: ");

            // 돌아가는 버튼 입력 시
            if (num == 0)
                break;
            // 플레이어 다이스 정보보기
            else if (num == 99)
            {
                GM.PrintPlayerDice();
                continue;
            }
            // player리스트에 없는거 입력
            if (Players.size() < (num) || (num) < 0)
            {
                UM.PrintInputWarning("잘못된 번호를 입력하셧습니다.");
                continue;
            }

            // 3. 플레이어 어디면을 고를지 선택
            while (true)
            {
                // 메인윈도우에 다이스 출력
                UM.ClearMenuBox();
                UM.ClearMainWindowBox();
                Menu = { "변경할 면을 선택하세요.", "0. 돌아가기" };
                UM.PrintMenuBox(Menu);

                Players[num-1].GetDice().PrintActionInfo();

                // 메인메뉴에 변경할 다이스면 고르는 문구 출력

                int idx = UM.GetUserInputNumber("선택 입력: ");

                // 돌아가는 버튼 입력
                if (idx == 0)
                    break;

                // 다이스면을 벗어나는 인덱스 입력
                if (idx < 1 || idx > 6)
                {
                    UM.PrintInputWarning("잘못된 번호를 입력하셨습니다.");
                    continue;
                }


                // 다이스 교체준비 & 골드지불
                UM.ClearMenuBox();
                Action* oldaction = Players[num-1].GetDice().GetAction(idx-1);
                PlayerMoney -= 50;

                // [a] ------> [b]
                cout << "  [" << oldaction->GetActionName() << "]  ------->  [" << FundAction->GetActionName() << "]  " << endl;

                // 기존 다이스면은 setaction으로 자동으로 delete. 이제 FundAction은 Dice가 관리함
                Players[num-1].GetDice().SetAction(idx-1, FundAction);
                Players[num - 1].GetDice().PrintActionInfo();

                // 엔터 누르면 넘어감
                string str = "교체되었습니다. 현재 남은 골드 : " + to_string(PlayerMoney);
                UM.GetUserInputForWait(str);

                brk = true;
                return;
            }
        }
    }





    // 여기에 도달시 정상적으로 보내지지않은거니 메모리 릭 이슈를 막고자 delete
    if(nullptr != FundAction)
        delete FundAction;

    return;
}

void ShopManager::CheatShop(vector<Player>& Players)
{
    for (auto& player : Players)
    {
        for (int i = 0; i < 6; ++i)
        {
            player.GetDice().SetAction(i, TemplateManager::getInstance().CreateDebugAction(true));
        }
    }

}

void ShopManager::CheatShop2(vector<Player>& Players)
{
    for (auto& player : Players)
    {
        for (int i = 0; i < 6; ++i)
        {
            player.GetDice().SetAction(i, TemplateManager::getInstance().CreateDebugAction(false));
        }
    }
}
