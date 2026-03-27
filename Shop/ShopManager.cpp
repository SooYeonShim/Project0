#include "ShopManager.h"

// 살아있는 플레이어 체력 회복
void ShopManager::HealAllPlayer(vector<Player>& Players, int& PlayerMoney)
{
    if (PlayerMoney >= 50)
    {
        cout << "모든 플레이어 체력 회복" << endl;
        PlayerMoney -= 50;
    }
    else
    {
        cout << "보유 돈이 부족합니다." << endl;
    }

}

// 아이템 구매
void ShopManager::BuyItem(int& PlayerMoney)
{
    if (PlayerMoney >= 50)
    {
        cout << "아이템 구매 테스트" << endl;
        PlayerMoney -= 50;
        cout << "남은 돈 : " << PlayerMoney << endl;
    }
    else
    {
        cout << "보유 돈이 부족합니다." << endl;
    }
    

}

//상점 진입
void ShopManager::EnterShop(vector<Player>& Players, int& PlayerMoney)
{
    while (true)
    {
        int PlayerInput = 0;

        PrintShopUI(PlayerMoney);
        PlayerInput = GetUserInputNum();
        if (PlayerInput == 1)
        {
            HealAllPlayer(Players, PlayerMoney);
            break;
        }
        else if (PlayerInput == 2)
        {
            BuyItem(PlayerMoney);
            break;
        }
        else 
        {
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
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
    cout << "\n================================" << endl;
    cout << "          ★  상점  ★       " << endl;
    cout << "     플레이어 보유 돈 : " << PlayerMoney << "        " << endl;
    cout << "================================" << endl;
    cout << " 1. 플레이어 회복" << endl;
    cout << " 2. 아이템 구매" << endl;
    cout << " 3. 상점 나가기" << endl;
    cout << "--------------------------------" << endl;
}
