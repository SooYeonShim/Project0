#include "CustomStreamBuf.h"

void CustomStreamBuf::SetParameterCursorPos(int newLineLeftMargin, int newLineTopMargin, int scrollingEndTop, int scrollingStartBottom)
{
    if (newLineLeftMargin != -1)
    {
        NewLineLeftMargin = newLineLeftMargin;
    }

    if (newLineTopMargin != -1)
    {
        NewLineTopMargin = newLineTopMargin;
    }

    if (scrollingEndTop != -1)
    {
        ScrollingEndTop = scrollingEndTop;
    }

    if (scrollingStartBottom != -1)
    {
        ScrollingStartBottom = scrollingStartBottom;
    }
}

void CustomStreamBuf::SetPressEnterPos(int pressEnterPosX, int pressEnterPosY)
{
    if (pressEnterPosX != -1)
    {
        PressEnterPosX = pressEnterPosX;
    }

    if (pressEnterPosY != -1)
    {
        PressEnterPosY = pressEnterPosY;
    }
}

void CustomStreamBuf::SetIsScrolling(bool isScrollingSet)
{
    AddLeftMargin = false;

    if (ScrollingEndTop == -1 || ScrollingStartBottom == -1)
    {
        IsScrollingSet = false;
        return;
    }

    IsScrollingSet = isScrollingSet;


    std::string numberStr;

    Dest->sputn("\x1b[", 3);
    numberStr = std::to_string(ScrollingEndTop);
    Dest->sputn(numberStr.data(), numberStr.length());
    Dest->sputc(';');
    numberStr = std::to_string(ScrollingStartBottom);
    Dest->sputc('r');



    
}

void CustomStreamBuf::SetPressEnterWhenNewLine(bool active)
{
    PressEnterWhenNewLine = active;
}


std::streambuf::int_type CustomStreamBuf::overflow(int_type c)
{
    if (c == traits_type::eof()) return traits_type::eof();

    std::string numberStr;

    if (AddLeftMargin)
    {

        if (IsScrollingSet)
        {
            Dest->sputn("\x1b[", 2);
            numberStr = std::to_string(ScrollingEndTop);
            Dest->sputn(numberStr.data(), numberStr.length());
            Dest->sputc(';');
            numberStr = std::to_string(ScrollingStartBottom);
            Dest->sputn(numberStr.data(), numberStr.length());
            Dest->sputc('r');

        }

        // newLine 온 경우, LeftMargin 처리

        Dest->sputn("\x1b[", 2);
        
        numberStr = std::to_string(NewLineTopMargin);
        Dest->sputn(numberStr.data(), numberStr.length());
        Dest->sputc(';');

        numberStr = std::to_string(NewLineLeftMargin);
        Dest->sputn(numberStr.data(), numberStr.length());
        Dest->sputc('H');
    }

    if (c == '\n')
    {
        // 줄바꿈에 Enter 입력 활성화 된 경우에만 사용
        if (PressEnterWhenNewLine)
        {


            Dest->sputn("\x1b[", 2);
            numberStr = std::to_string(PressEnterPosY);            
            Dest->sputn(numberStr.data(), numberStr.length());
            Dest->sputc(';');

            numberStr = std::to_string(PressEnterPosX);
            Dest->sputn(numberStr.data(), numberStr.length());
            Dest->sputc('H');
            Dest->sputn("[ Press Enter ]", sizeof("[ Press Enter ]"));

            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

            // Press 엔터 이후, 커서 위치 결정
            Dest->sputn("\x1b[", 2);
            numberStr = std::to_string(NewLineTopMargin);
            Dest->sputn(numberStr.data(), numberStr.length());

            Dest->sputc(';');

            numberStr = std::to_string(NewLineLeftMargin);
            Dest->sputn(numberStr.data(), numberStr.length());            
            Dest->sputc('H');
        }


        
        AddLeftMargin = true;
    }
    else
    {
        AddLeftMargin = false;
    }

    
    return Dest->sputc(c);
}
