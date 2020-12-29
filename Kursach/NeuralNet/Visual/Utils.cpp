#pragma once
#include "Utils.h"

COORD operator+(COORD a, COORD const& b) {

    return { a.X + b.X, a.Y + b.Y };
}

COORD operator-(COORD a, COORD const& b) {

    return { a.X - b.X, a.Y - b.Y };
}
//const COORD ZERO_COORD = { 0,0 };

namespace Visual
{
    
    

    bool Utils::Question(std::string text)
    {
        Visual::TConsole* console = Visual::TConsole::GetInstance();
        COORD startPos = console->Where();


        char input;

        do
        {
            std::cout << text + "? (y/n) ";
            std::cin >> input;

            COORD nPos = console->Where();
            console->GotoXY(startPos);
            console->DelLine(nPos.Y - startPos.Y + 1);

        } while (std::tolower(input) != 'y' && std::tolower(input) != 'n');


        console->GotoXY(startPos);

        return std::tolower(input) == 'y';
    }

    void Utils::Out(std::string text)
    {
        Visual::TConsole* console = Visual::TConsole::GetInstance();
        COORD startPos = console->Where();

        std::cout << text<<" (press any key)";
        console->ReadKey();

        COORD nPos = console->Where();
        console->GotoXY(startPos);
        console->DelLine(nPos.Y - startPos.Y + 1);
    }

}