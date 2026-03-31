#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "Character.h"
#include "Player.h"
#include "Action.h"
#include "GameEnums.h"
#include "Monster.h"

#include "CustomStreamBuf.h"
#include "StatusEffect.h"


// --- ANSI 색상 코드 정의 ---
/**
 *
 * EMCA-48 문서에서
 * 8.3.117 - SELECT GRAPHIC RENDITION
 *
 */

constexpr const char* RED = "\x1b[31m";
constexpr const char* RESET = "\x1b[0m";
constexpr const char* BOLD = "\x1b[1m";
constexpr const char* YELLOW = "\x1b[33m";
constexpr const char* CYAN = "\x1b[36m";
constexpr const char* WHITE = "\x1b[37m";

constexpr const char* SCREEN_ALT = "\x1b[?1049h";
constexpr const char* SCREEN_MAIN = "\x1b[?1049l";




class UIManager {
public:
    static UIManager& getInstance()
    {
        static UIManager instance; // 최초 1회만 생성
        return instance;
    }


    // 시작시 가장 먼저 호출되는 함수
    // 콘솔 화면을 최대로 키우고 Enter을 눌러 시작하도록 요청함
    void WaitForStart(std::string msg);

    // TempScreen에서 Enter 받는 거 대기용으로 사용
    void WaitForEnterInTempScreen(std::string msg);

    void PrintMessage(std::string message);

    // HP 출력방식
    // 검은색 - 10 이하에서 비어있는 부분
    // 빨강색 - 10 이하에서 남은 것
    // 주황색 - 20 이하에서 남은 것
    // 초록색 - 30 이하에서 남은 것
    /**
     *
     * HP가 25인 경우
     *
     * [ 초록색 초록색 초록색 초록색 초록색 주황색 주황색 주황색 주황색 주황색 ]
     * 
     */    
    void PrintHP(int HP);

    void PrintShield(int shield);

    void PrintTarget(Action* action);

    void PrintEffectStatus(const vector<StatusEffect>& effects);

    void PrintBattleBoard(std::vector<Player>& players, std::vector<Monster>& monsters);

    // MainWindow쪽으로 커서를 설정 함
    void CursorScrollSet() const;

    // 위쪽 메뉴 박스를 비움
    void ClearMainWindowBox();

    // 외곽선을 그림
    void DrawBorder();

    // 문자열 입력받음
    string GetUserInput(std::string message);

    // 숫자 입력 받음
    int GetUserInputNumber(std::string message);

    // 엔터 입력 받음 -> 엔터 입력 전까지 블록킹 효과
    void GetUserInputForWait(std::string msg);
    void PrintInputWarning(std::string msg);
    // 입력라인 설명 지움
    void InputLineClear() const;

    // MainWindow 아래에 있는 Menu 박스의 텍스트를 초기화 함
    void ClearMenuBox() const;

    // 하단 박스에 메뉴를 출력함
    void PrintMenuBox(const std::vector<std::string>& menus);

    // isNewLine 을 받는 이유,
    // 새로 줄 갱신을 해서 그릴 때는 NewLine을 넣고 그림 -> 기존의 텍스트들이 밀림
    // 하지만, 이미 있는 줄을 사용할 때는 NewLine을 넣지 않고 그림 -> 기존의 텍스트들이 밀리지 않음.
    // 가로에 스프라이트들을 배치할 때 사용
    void PrintMonsterSprite(std::string monsterType, int startColumn, bool isNewLine = false);

    // isNewLine 을 받는 이유,
    // 새로 줄 갱신을 해서 그릴 때는 NewLine을 넣고 그림 -> 기존의 텍스트들이 밀림
    // 하지만, 이미 있는 줄을 사용할 때는 NewLine을 넣지 않고 그림 -> 기존의 텍스트들이 밀리지 않음.
    // 가로에 스프라이트들을 배치할 때 사용    
    void PrintPlayerSprite(Player& player, int startColumn, bool isNewLine = false) const;


    void CreateNewScreenForStoryPrint();

    void CloseAnyTempScreen();

    ~UIManager()
    {
        if (StreamBuffer != nullptr)
        {
            delete StreamBuffer;
            StreamBuffer = nullptr;
        }
    }



private:
    static constexpr const char* BLOCK_BLACK = "\x1b[30m■\x1b[0m";
    static constexpr const char* BLOCK_RED = "\x1b[31m■\x1b[0m";
    static constexpr const char* BLOCK_YELLOW = "\x1b[33m■\x1b[0m";
    static constexpr const char* BLOCK_GREEN = "\x1b[32m■\x1b[0m";
    static constexpr const char* BLOCK_SKY = "\x1b[36m■\x1b[0m";

    static constexpr const char* HP_BLOCKS[4] = { BLOCK_BLACK, BLOCK_RED, BLOCK_YELLOW, BLOCK_GREEN };

    int Width = 150;
    int Height = 46;
    int LeftMargin = 4;

    // 위쪽 Window Row 시작지점 표시 -> 아래에서 위로 쌓이는 구조
    int StartStatusRow = 35;

    // 아래쪽 Window Row 시작지점 표시 -> 위에서 아래로 쌓이는 구조
    int StartMenuRow = 40;

    // 사용자 입력을 받는 Row
    int InputRow = 50;
    int CurrentWindowIndex = 1;


    std::streambuf* mOriginalBuffer = nullptr;

    // \n마다 Blocking을 넣어줄 버퍼
    CustomStreamBuf* StreamBuffer = nullptr;

    bool IsIntercepting = false;
    bool AtStartOfLine = true;


    /**
     *
     * 외부에 두는 게 맞다고 생각하지만,
     * Default로 UImanager에서 제공하는 방식대로 출력을 사용해도
     * 현재까지는 해제하거나 활성화 할 일이 없었기 때문에
     * 필요한 일이 생기면 그때 Public으로 옮기겠음
     * 
     */
    // stream Buffer 가로채기 활성화
    void EnableStreamMarginHook();

    // stream Buffer 가로채기 해제
    void DisableStreamMarginHook();


    UIManager();

};
