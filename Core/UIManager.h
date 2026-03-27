#pragma once
#define NOMINMAX // windows.h의 max 매크로 충돌 방지
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

// --- ANSI 색상 코드 정의 ---
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

#include "Character.h"
#include "Player.h"
#include "Action.h"
#include "GameEnums.h"
#include "Monster.h"


class UIManager {
public:
    // [1] 콘솔 초기화 (색상 및 UTF-8 활성화)
    static void InitConsole() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        SetConsoleOutputCP(CP_UTF8);
    }

    // [2] 화면 전체 지우기 (Windows API 방식)
    static void ClearScreen() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coordScreen = { 0, 0 };
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
        DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
        SetConsoleCursorPosition(hConsole, coordScreen);
    }

    // [3] 한글 폭 계산 (UTF-8 기준)
    static int GetVisualWidth(const std::string& str) {
        int width = 0;
        for (size_t i = 0; i < str.length(); ++i) {
            if (static_cast<unsigned char>(str[i]) > 127) {
                width += 2;
                i += 2; // UTF-8 한글 3바이트 대응
            }
            else {
                width += 1;
            }
        }
        return width;
    }

    // [4] 고정 폭 문자열 생성
    static std::string Fit(std::string str, int size) {
        int cur = GetVisualWidth(str);
        if (size <= cur) return str;
        return str + std::string(size - cur, ' ');
    }

    // [5] HP 게이지 바 생성
    static std::string GetHPBar(int cur, int max, int width = 10) {
        float percentage = (max > 0) ? (float)cur / max : 0;
        int filled = (int)(width * percentage);
        if (filled < 0) filled = 0;

        std::string bar = "[";
        for (int i = 0; i < width; ++i) {
            bar += (i < filled) ? "■" : " ";
        }
        bar += "]";

        if (percentage > 0.5f) return std::string(GREEN) + bar + RESET;
        if (percentage > 0.2f) return std::string(YELLOW) + bar + RESET;
        return std::string(RED) + bar + RESET;
    }

    // [6] 상태 아이콘 생성
    static std::string GetStatusIcon(bool isReady, bool isDead) {
        if (isDead)  return std::string(RED) + " [X] " + RESET;
        if (isReady) return std::string(GREEN) + " [V] " + RESET;
        return std::string(YELLOW) + " [ ] " + RESET;
    }

    // [7] 메인 전투 현황판
    static void PrintBattleBoard(std::vector<Player>& players, std::vector<Monster>& monsters) {
        const int WIDTH = 95;
        std::string line(WIDTH, '=');
        std::cout << BOLD << CYAN << line << RESET << "\n";
        std::cout << "  " << BOLD << YELLOW << "BATTLE STATUS DASHBOARD" << RESET << "\n";
        std::cout << CYAN << line << RESET << "\n";
        std::cout << "  " << Fit("NAME", 16) << " | " << Fit("HP GAUGE", 14) << " | " << Fit("ACTION", 18) << " | TARGET\n";
        std::cout << std::string(WIDTH, '-') << "\n";

        auto DrawChar = [](Character& c, std::string color) {
            std::cout << color << "  " << Fit(c.GetName(), 16) << RESET << " | ";
            if (c.GetIsDead()) {
                std::cout << RED << Fit("[ ELIMINATED ]", 14) << RESET << " | " << Fit("-", 18) << " | -\n";
            }
            else {
                std::cout << GetHPBar(c.GetHP(), c.GetMaxHP()) << " | ";
                Action* act = c.GetCurrentAction();
                if (act) {
                    std::cout << YELLOW << Fit(act->GetActionName(), 18) << RESET << " | ";
                    auto targets = act->GetTatgerCharacters();
                    if (targets.empty()) std::cout << "-";
                    else for (auto* t : targets) std::cout << CYAN << "[" << t->GetName() << "] " << RESET;
                }
                else {
                    std::cout << Fit("WAITING...", 18) << " | -";
                }
                std::cout << "\n";
            }
            };

        for (auto& p : players) DrawChar(p, GREEN);
        std::cout << std::string(WIDTH, '.') << "\n";
        for (auto& m : monsters) DrawChar(m, RED);
        std::cout << BOLD << CYAN << line << RESET << "\n\n";
    }

    // [8] 액션 설정 현황판
    static void PrintActionStatus(std::vector<Player>& players) {
        const int WIDTH = 65;
        std::string line(WIDTH, '=');
        std::cout << BOLD << CYAN << line << RESET << "\n";
        std::cout << "  " << BOLD << "PARTY ACTION SELECTION STATUS" << RESET << "\n";
        std::cout << CYAN << line << RESET << "\n";
        std::cout << "  " << Fit("STATUS", 8) << " | " << Fit("PLAYER", 16) << " | SELECTED ACTION\n";
        std::cout << std::string(WIDTH, '-') << "\n";

        for (auto& p : players) {
            bool hasAction = (p.GetCurrentAction() != nullptr);
            std::cout << GetStatusIcon(hasAction, p.GetIsDead()) << " | ";
            std::cout << (p.GetIsDead() ? RED : WHITE) << Fit(p.GetName(), 16) << RESET << " | ";
            if (p.GetIsDead()) std::cout << RED << "ELIMINATED" << RESET;
            else if (hasAction) std::cout << YELLOW << BOLD << ">> " << p.GetCurrentAction()->GetActionName() << RESET;
            else std::cout << std::string(4, ' ') << "... Selecting";
            std::cout << "\n";
        }
        std::cout << BOLD << CYAN << line << RESET << "\n\n";
    }

    // [9] 박스형 메뉴 출력
    static void PrintMenu(const std::vector<std::string>& menus, int width = 60) {
        // 테두리 상단 (좌측 여백 2칸 유지)
        std::string edge = "  +" + std::string(width - 4, '-') + "+";
        std::cout << YELLOW << edge << RESET << "\n";

        for (const std::string& menu : menus) {
            // [중요] 내부에서 번호를 생성하지 않고, 넘겨받은 menu 문자열을 그대로 사용
            // 만약 번호를 자동으로 붙이고 싶다면 이 줄을 std::string text = std::to_string(i + 1) + ". " + menu; 로 수정
            const std::string& text = menu;

            int vWidth = GetVisualWidth(text);

            // 중앙 정렬을 위한 가용 여백 (테두리와 내부 공백 제외)
            int totalPadding = width - 6 - vWidth;
            if (totalPadding < 0) totalPadding = 0; // 문자열이 너무 길 경우 대비

            int leftPad = totalPadding / 2;
            int rightPad = totalPadding - leftPad;

            // 출력부
            std::cout << YELLOW << "  | " << RESET; // 왼쪽 벽
            std::cout << std::string(leftPad, ' ') << BOLD << text << RESET; // 내용
            std::cout << std::string(rightPad, ' ') << YELLOW << " |" << RESET << "\n"; // 오른쪽 벽
        }

        // 테두리 하단
        std::cout << YELLOW << edge << RESET << "\n";
    }

    // [10] 입력 처리 (숫자 전용)
    static int GetInput() {
        int choice;
        while (true) {
            std::cout << BOLD << WHITE << "  입력 >> " << RESET;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::cout << RED << "  [!] 숫자를 입력해주세요." << RESET << "\n";
                continue;
            }
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return choice;
        }
    }

    // [11] 시스템 메시지 및 대기
    static void Wait(std::string msg) {
        std::cout << "\n" << BOLD << YELLOW << "  " << RESET << msg << CYAN << " [PRESS ENTER]" << RESET;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }

    // [12] 시스템 메세지
    static void PrintMessage(std::string message, bool bNewLine = false) {
        std::cout << BOLD << WHITE << " [SYSTEM] " << RESET << message << std::endl;
        if (bNewLine) {
            cout << std::endl;
        }
    }
};
