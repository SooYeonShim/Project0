#include "GameManager.h"

using namespace std;

void GameManager::InitializeCharacter(vector<Player>& Players)
{
    int PlayerCount = 0;
    string NickName;

    for (int i = 0; i < 2; ++i)
    {
        int jobChoice;

        cout << i + 1 << "번 플레이어 이름: ";
        getline(cin, NickName);

        cout << "직업 선택 (0:Fighter, 1:Archer, 2:Defender, 3:Rogue): ";
        cin >> jobChoice;
        cin.ignore();

        // 입력받은 숫자를 JobType으로 변환하여 추가
        Players.push_back(Player(NickName, static_cast<JobType>(jobChoice)));
    }

}

void GameManager::GameStart()
{
    InitializeCharacter(Players);
    //초기화 정상작동 확인
    cout << "첫 번째 플레이어 이름: " << Players[0].GetNickname() << " 직업: " << static_cast<int>(Players[0].GetJobType()) << endl;
    cout << "두 번째 플레이어 이름: " << Players[1].GetNickname() << " 직업: " << static_cast<int>(Players[1].GetJobType()) << endl;

}

void GameManager::BattleResult(bool Result)
{

}

