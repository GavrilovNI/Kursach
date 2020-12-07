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
            uint32_t n = nPos.Y - startPos.Y;
            for (size_t i = 0; i < n; i++)
            {
                console->DelLine();
            }

        } while (std::tolower(input) != 'y' && std::tolower(input) != 'n');


        console->GotoXY(startPos);

        return std::tolower(input) == 'y';
    }

}