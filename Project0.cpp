// Project0.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <GameManager.h>
#include "UIManager.h"



int main()
{
    // 콘솔 화면에서 커서를 움직여서 화면을 구성할 거기 때문에, 기존의 콘솔 텍스트를 전부 삭제함 
    system("cls");

    UIManager::getInstance().WaitForStart("콘솔창 화면을 전체 화면으로 바꿔주세요. 이후, 엔터를 눌러주세요.");
    std::cout << "\x1b[2J";
    std::cout << "\x1b[3J";
    std::cout << "\x1b[H";

    //std::cout << "Game Start!\n";

    UIManager manager = UIManager::getInstance();
    manager.DrawBorder();

    cout << "모험을 떠날 영웅들이 모였습니다" << std::endl;  


    GameManager& gm = GameManager::getInstance();

    gm.GameStart();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
