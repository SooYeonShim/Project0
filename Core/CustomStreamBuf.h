#pragma once
#include <iostream>
#include <string>


/*
 *  std::cout << "\x1b[14;34H";
    std::cout << "\x1b[0:34r";
 *
 */

class CustomStreamBuf : public std::streambuf {
public:
    // 인자를 받는 생성자만 존재함
    CustomStreamBuf(std::streambuf* original) : Dest(original) {}


    // -1인 경우 기존 값 사용, 아닌 경우 덮어쓰기
    void SetParameterCursorPos(int newLineLeftMargin, int newLineTopMargin, int scrollingEndTop, int ScrollingStartBottom);

    // -1인 경우 기존 값 사용, 아닌 경우 덮어쓰기
    void SetPressEnterPos(int PressEnterPosX, int PressEnterPosY);

    // SetParameterCursorPos으로 스크롤 범위를 정하고 호출할 것
    // 스크롤 범위가 유효하지 않으면 isScrollingSet 활성화 X
    void SetIsScrolling(bool isScrollingSet);

    // std::cout에서 NewLine을 받으면 Enter를 받기 전까지 Blocking 시키는 기능을 활성화 할지
    void SetPressEnterWhenNewLine(bool active);

protected:
    int_type overflow(int_type c) override;

private:
    std::streambuf* Dest;

    bool AddLeftMargin = true;

    int NewLineLeftMargin = 34;
    int NewLineTopMargin = 14;

    int PressEnterPosX = 34;
    int PressEnterPosY = 16;
    

    bool PressEnterWhenNewLine = false;
    bool IsScrollingSet = false;


    // 아래에서 위로 올라가는 방식의 스크롤링,
    int ScrollingEndTop = -1; //0;
    int ScrollingStartBottom = -1; //14;

};
