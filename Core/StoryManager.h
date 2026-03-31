#pragma once



class StoryManager
{
public:
    static StoryManager& getInstance()
    {
        static StoryManager instance; // 최초 1회만 생성
        return instance;
    }

// 스토리 목록
public:
    // 번호입력시 해당 스토리 플레이
    // 엔딩은 98 게임오버는 99
    // 0 : 프롤로그, 1: 스테이지1, 2: 스테이지2, 3: 스테이지3, 4: 보스전
    void StoryByIndex(int _idx);

    // 프롤로그
    void Prologue();

    // 스테이지1
    void Stage1Story();

    // 스테이지2
    void Stage2Story();

    // 스테이지3
    void Stage3Story();

    // boss
    void BossStageStory();

    // 엔딩
    void EndingStory();

    // 전멸
    void GameOverStory();

private:
    // 생성자를 private으로 막음
    StoryManager() {}

    // 복사/대입도 막음
    StoryManager(const StoryManager&) = delete;
    StoryManager& operator=(const StoryManager&) = delete;

};

