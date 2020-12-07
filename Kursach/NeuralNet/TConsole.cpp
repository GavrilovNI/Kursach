#pragma once

#include "TConsole.h"
#include "Utils.h"

namespace Visual
{

    TConsole* TConsole::_instance = nullptr;
    TConsole* TConsole::GetInstance()
    {
        if (_instance == nullptr) {
            _instance = new TConsole();
        }
        return _instance;
    }

	TConsole::TConsole() :In(std::cin), Out(std::cout)
    {
        InputHandle = GetStdHandle(STD_INPUT_HANDLE);
        OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(OutputHandle, &ScreenBufInfo);
    }

    TConsole::~TConsole()
    {
        if (this == _instance)
            _instance = nullptr;
    }

    CONSOLE_SCREEN_BUFFER_INFO TConsole::GetScreenBufferInfo() const
    {
        CONSOLE_SCREEN_BUFFER_INFO result;
        GetConsoleScreenBufferInfo(OutputHandle, &result);
        return result;
    }

    void TConsole::UpdateScreenBufferInfo()
    {
        GetConsoleScreenBufferInfo(OutputHandle, &ScreenBufInfo);
    }

    WORD TConsole::GetAttributes() const
    {
        return ScreenBufInfo.wAttributes;
    }

    
    char TConsole::GetChar(COORD coord)
    {
        char result;
        DWORD num_read;
        if (ReadConsoleOutputCharacter(OutputHandle, (LPTSTR)&result, 1, coord, (LPDWORD)&num_read) == 0)
            return result;
        else
            return emptyChar;
    }

    void TConsole::SetAttribute(WORD atribute, bool value)
    {
        UpdateScreenBufferInfo();
        WORD TextAttr = GetAttributes();
        if (value)
        {
            TextAttr = TextAttr | atribute;
        }
        else
        {
            TextAttr = TextAttr & ~atribute;
        }

        SetConsoleTextAttribute(OutputHandle, TextAttr);
    }
    void TConsole::SetAttribute(WORD attribute, WORD place)
    {
        UpdateScreenBufferInfo();
        WORD TextAttr = GetAttributes();
        TextAttr = attribute | (TextAttr & ~place);
        SetConsoleTextAttribute(OutputHandle, TextAttr);
    }

    WORD TConsole::GetAttribute(WORD attribute)
    {
        WORD TextAttr = GetAttributes();
        return (TextAttr & attribute);
    }

    ConsoleSettings TConsole::GetSettings()
    {
        ConsoleSettings result;
        result.color.bgColor = GetBackgroundColor();
        result.color.textColor = GetTextColor();
        result.lVertical = IsLVertical();
        result.rVertical = IsRVertical();
        result.horisontal = IsHorisontal();
        return result;
    }

    void TConsole::SetSettings(const ConsoleSettings settings)
    {
        SetBackgroundColor(settings.color.bgColor);
        SetTextColor(settings.color.textColor);
        SetLVertical(settings.lVertical);
        SetRVertical(settings.rVertical);
        SetHorisontal(settings.horisontal);
    }

    bool TConsole::ClrEol()
    {
        DWORD NOAW;
        return FillConsoleOutputCharacter(OutputHandle, emptyChar,
            ScreenBufInfo.dwSize.X - ScreenBufInfo.dwCursorPosition.X,
            ScreenBufInfo.dwCursorPosition, &NOAW);
    }
    void TConsole::ClrScr()
    {
        DWORD NOAW;
        FillConsoleOutputCharacter(OutputHandle, emptyChar, ScreenBufInfo.dwSize.X * ScreenBufInfo.dwSize.Y,
            {0, 0}, &NOAW);
    }
    void TConsole::Delay(WORD MS) const
    {
        SleepEx(MS, FALSE);
    }
    void TConsole::DelLine()
    {
        auto scrbufInfo = GetScreenBufferInfo();
        CHAR_INFO CI{ (WCHAR)emptyChar, scrbufInfo.wAttributes };
        COORD Coord{ scrbufInfo.srWindow.Left, (SHORT)WhereY() };
        scrbufInfo.srWindow.Top = Coord.Y + 1;
        //DWORD Size, Count;
        //Size = ScreenBufInfo.srWindow.Right - ScreenBufInfo.srWindow.Left + 1;
        ScrollConsoleScreenBuffer(OutputHandle, &scrbufInfo.srWindow, 0, Coord, &CI);
        //FillConsoleOutputAttribute(OutputHandle, ScreenBufInfo.wAttributes, Size, Coord, &Count);
    }
    bool TConsole::GotoXY(COORD coord)
    {
        ScreenBufInfo.dwCursorPosition = coord;
        return SetConsoleCursorPosition(OutputHandle, ScreenBufInfo.dwCursorPosition);
    }
    void TConsole::Move(COORD dir)
    {
        GotoXY(Where() + dir);
    }
    void TConsole::InsLine()
    {
        UpdateScreenBufferInfo();
        SMALL_RECT ScreenRect = ScreenBufInfo.srWindow;
        ScreenRect.Top = ScreenBufInfo.dwCursorPosition.Y - 1 + ScreenBufInfo.srWindow.Top;
        ScreenRect.Bottom = ScreenBufInfo.srWindow.Bottom - 1;
        CHAR_INFO CI;
        CI.Char.UnicodeChar = ' ';
        CI.Attributes = ScreenBufInfo.wAttributes;
        COORD Coord;
        Coord.X = ScreenRect.Left;
        Coord.Y = ScreenRect.Top + 1;
        DWORD dwSize = ScreenRect.Right - ScreenRect.Left + 1;
        ScrollConsoleScreenBuffer(OutputHandle, &ScreenRect, 0, Coord, &CI);
        Coord.Y--;
        DWORD dwCount;
        FillConsoleOutputAttribute(OutputHandle, ScreenBufInfo.wAttributes, dwSize, Coord, &dwCount);
    }
    bool TConsole::KeyPressed() const
    {
        bool flag = false;
        DWORD NumberOfEvents;
        GetNumberOfConsoleInputEvents(InputHandle, &NumberOfEvents);
        if (NumberOfEvents > 0)
        {
            INPUT_RECORD IR;
            DWORD NumRead;
            if (PeekConsoleInput(InputHandle, &IR, 1, &NumRead))
            {
                if ((IR.EventType == KEY_EVENT) && (IR.Event.KeyEvent.bKeyDown)) flag = true;
                else ReadConsoleInput(InputHandle, &IR, 1, &NumRead);
            }
        }
        return flag;
    }
    WCHAR TConsole::ReadKey() const
    {
        DWORD NumRead;
        INPUT_RECORD IR;
        do
        {
            do
            {
            } while (!KeyPressed());
            ReadConsoleInput(InputHandle, &IR, 1, &NumRead);
        } while (IR.Event.KeyEvent.uChar.UnicodeChar == 0);
        return IR.Event.KeyEvent.uChar.UnicodeChar;
    }
    void TConsole::SetBackgroundColor(Color Color)
    {
        //SetAttribute((WORD)Color << 4, (WORD)0x0f);
        UpdateScreenBufferInfo();
        WORD TextAttr = ScreenBufInfo.wAttributes;
        TextAttr = ((int)Color << 4) | (TextAttr & ~0xF0);
        SetConsoleTextAttribute(OutputHandle, TextAttr);
    }
    void TConsole::SetTextColor(Color Color)
    {
        //SetAttribute((WORD)Color, (WORD)0x0f);
        UpdateScreenBufferInfo();
        WORD TextAttr = ScreenBufInfo.wAttributes;
        TextAttr = (int)Color | (TextAttr & ~0x0F);
        SetConsoleTextAttribute(OutputHandle, TextAttr);
    }
    Color TConsole::GetTextColor()
    {
        //return (Color)GetAttribute(0x0f);
        UpdateScreenBufferInfo();
        WORD TextAttr = ScreenBufInfo.wAttributes;

        return (Color)(TextAttr & 0x0F);
    }
    Color TConsole::GetBackgroundColor()
    {
        //return (Color)(GetAttribute(0xf0) >> 4);
        UpdateScreenBufferInfo();
        WORD TextAttr = ScreenBufInfo.wAttributes;

        int x = (TextAttr >> 4) & 0x0F;
        x = (TextAttr & 0xF0)>>4;

        return (Color)((TextAttr >> 4) & 0x0F);
    }



    void TConsole::SetUnderscore(bool value)
    {
        SetAttribute(COMMON_LVB_UNDERSCORE, value);
    }
    bool TConsole::IsUnderscore()
    {
        return GetAttribute(COMMON_LVB_UNDERSCORE);
    }

    void TConsole::SetLVertical(bool value)
    {
        SetAttribute(COMMON_LVB_GRID_LVERTICAL, value);
    }
    bool TConsole::IsLVertical()
    {
        return GetAttribute(COMMON_LVB_GRID_LVERTICAL);
    }
    void TConsole::SetRVertical(bool value)
    {
        SetAttribute(COMMON_LVB_GRID_RVERTICAL, value);
    }
    bool TConsole::IsRVertical()
    {
        return GetAttribute(COMMON_LVB_GRID_RVERTICAL);
    }
    void TConsole::SetHorisontal(bool value)
    {
        SetAttribute(COMMON_LVB_GRID_HORIZONTAL, value);
    }
    bool TConsole::IsHorisontal()
    {
        return GetAttribute(COMMON_LVB_GRID_HORIZONTAL);
    }
    COORD TConsole::Where()
    {
        UpdateScreenBufferInfo();
        return ScreenBufInfo.dwCursorPosition;
    }
    int TConsole::WhereX()
    {
        UpdateScreenBufferInfo();
        return ScreenBufInfo.dwCursorPosition.X;
    }
    int TConsole::WhereY()
    {
       UpdateScreenBufferInfo();
        return ScreenBufInfo.dwCursorPosition.Y;
    }
    void TConsole::Window(BYTE X, BYTE Y)
    {
        SMALL_RECT ConsoleRect;
        ConsoleRect.Top = 0;
        ConsoleRect.Left = 0;
        ConsoleRect.Right = X - 1;
        ConsoleRect.Bottom = Y - 1;
        COORD BufSize;
        BufSize.X = X;
        BufSize.Y = Y;
        SetConsoleScreenBufferSize(OutputHandle, BufSize);
        SetConsoleWindowInfo(OutputHandle, TRUE, &ConsoleRect);
        GotoXY({ 0, 0 });
    }
    COORD TConsole::GetWindowSize()
    {
        UpdateScreenBufferInfo();
        short x, y;
        x = ScreenBufInfo.srWindow.Right - ScreenBufInfo.srWindow.Left + 1;
        y = ScreenBufInfo.srWindow.Bottom - ScreenBufInfo.srWindow.Top + 1;

        return { x, y };
    }

}