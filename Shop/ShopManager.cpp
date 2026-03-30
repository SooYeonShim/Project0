#include "ShopManager.h"

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
        UM.PrintMessage("모든 플레이어 체력 회복");
        PlayerMoney -= 50;
    }
    else
    {
        UM.PrintInputWarning("보유 돈이 부족합니다.");
    }

}

// 아이템 구매
void ShopManager::BuyItem(int& PlayerMoney)
{
    
    InventoryManager& IM = InventoryManager::getInstance();
    UIManager& UM = UIManager::getInstance();

    UM.ClearMenuBox();
    vector<string> Menu = { "구매하고 싶은 아이템을 선택해주세요", "", "1. 힐링 포션" };
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
            UM.PrintInputWarning("보유 돈이 부족합니다.");
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
        else if (PlayerInput == 0)
        {
            break;
        }
        else 
        {
            UM.PrintInputWarning("0~3자리 숫자를 입력해주세요.");
        }

    }
}


// 유저 입력 받은 후 입력 값 반환
int ShopManager::GetUserInputNum()
{
    int PlayerInput;
    while (true)
    {
        cout << "선택 입력 : ";
        cin >> PlayerInput;
        cout << endl;
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


// 상점 UI 출력
void ShopManager::PrintShopUI(int PlayerMoney)
{
    UIManager& UM = UIManager::getInstance();

    UM.ClearMenuBox();

    vector<string> Menu;

    Menu = { "     ★  상점  ★", "플레이어 보유 돈: " + to_string(PlayerMoney), "1. 플레이어 회복", "2. 아이템 구매", "3. 인벤토리 확인", "0. 상점 나가기" };
    UM.PrintMenuBox(Menu);
}
