#pragma once

#include<windows.h>
#include<iostream>

namespace Visual
{

    enum class Color
    {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHTGRAY = 7,
        DARKGRAY = 8,
        LIGHTBLUE = 9,
        LIGHTGREEN = 10,
        LIGHTRED = 12,
        LIGHTMAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };

    struct ColorSettings
    {
        Color bgColor;
        Color textColor;
    };

    struct ConsoleSettings
    {
        ColorSettings color;
        bool lVertical;
        bool rVertical;
        bool horisontal;
        bool underscore;
    };

    class TConsole
    {
    private:
        const char emptyChar = 0;
        static TConsole* _instance;

        HANDLE InputHandle;
        HANDLE OutputHandle;
        CONSOLE_SCREEN_BUFFER_INFO ScreenBufInfo;

        TConsole();
        ~TConsole();

        CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo() const;
        void UpdateScreenBufferInfo();

        void SetAttribute(WORD attribute, WORD place);
        void SetAttribute(WORD attribute, bool value);
        WORD GetAttribute(WORD attribute);
        WORD GetAttributes() const;
    public:

        static TConsole* GetInstance();

        std::ostream& Out;
        std::istream& In;

        ConsoleSettings GetSettings();

        char GetChar(COORD coord);

        void Fill(SMALL_RECT rect, char value)
        {
            COORD prevPos = Where();

            std::string empty(rect.Right - rect.Left, value);
            COORD linePos = { rect.Left, rect.Top };
            for (SHORT i = 0; i < rect.Bottom - rect.Top; i++)
            {
                GotoXY(linePos);
                std::cout << empty;
                linePos.Y++;
            }

            GotoXY(prevPos);
        }

        void SetSettings(const ConsoleSettings settings);
        bool ClrEol();
        void ClrScr();
        void Delay(WORD MS) const;
        void DelLine(uint32_t count = 1);
        bool GotoXY(COORD coord);
        void Move(COORD dir);
        void InsLine();
        bool KeyPressed() const;
        WCHAR ReadKey() const;
        void SetBackgroundColor(Color Color);
        void SetTextColor(Color Color);
        Color GetTextColor();
        Color GetBackgroundColor();

        void SetUnderscore(bool value);
        bool IsUnderscore();

        void SetLVertical(bool value);
        bool IsLVertical();
        void SetRVertical(bool value);
        bool IsRVertical();
        void SetHorisontal(bool value);
        bool IsHorisontal();
        COORD Where();
        int WhereX();
        int WhereY();
        void Window(BYTE X, BYTE Y);
        COORD GetWindowSize();
    };

}


