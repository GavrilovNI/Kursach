#pragma once
#include <string>
#include <iostream>
#include "TConsole.h"

COORD operator+(COORD a, COORD const& b);
COORD operator-(COORD a, COORD const& b);

namespace Visual
{
	static const COORD COORD_ZERO = { 0,0 };

	class Utils
	{
	public:
        static bool Question(std::string text);
	};

    

    
}