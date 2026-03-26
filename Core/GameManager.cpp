#include "GameManager.h"

using namespace std;

void GameManager::InitializeCharacter(vector<Player>& Players)
{
    int PlayerCount = 0;
    string NickName;

    for (int i = 0; i < 1; ++i)
    {
        int jobChoice;

        cout << i + 1 << "번 플레이어 이름: ";
        getline(cin, NickName);

        cout << "직업 선택 (0:Fighter, 1:Archer, 2:Defender, 3:Rogue): ";
        cin >> jobChoice;
        cin.ignore();

        // 입력받은 숫자를 JobType으로 변환하여 추가
        Players.push_back(Player(10, Dice(), NickName, static_cast<JobType>(jobChoice)));
    }

}

void GameManager::GameStart()
{

    BattleManager& BM = BattleManager::getInstance();

    //플레이어 캐릭터 초기화
    InitializeCharacter(Players);
    //초기화 정상작동 확인
    cout << "첫 번째 플레이어 이름: " << Players[0].GetNickname() << " 직업: " << static_cast<int>(Players[0].GetJobType()) << endl;
    //cout << "두 번째 플레이어 이름: " << Players[1].GetNickname() << " 직업: " << static_cast<int>(Players[1].GetJobType()) << endl;

    //처음 스테이지 초기화
    CurrentStage = 1;

    //스테이지가 3이 되기전까지 전투 반복
    while (CurrentStage != 3)
    {
        //전투 돌입
        BattleResult(BM.Battle(Players, CurrentStage));

        //게임 종료 후 스테이지 증가 
        ++CurrentStage;

    }

    //게임 종료
    return;

}

// 전투 결과에 따라 게임 종료 혹은 경험치&아이템 획득
void GameManager::BattleResult(bool Result)
{
    if (Result == true)
    {
        // 경험치 및 아이템 획득
        return;
    }
    else
    {
        // 플레이어 캐릭터 전멸 게임 종료
        return;
    }

}

