#pragma once
#include <string>
#include <iostream>
#include <functional>
#include "TConsole.h"

COORD operator+(COORD a, COORD const& b);
COORD operator-(COORD a, COORD const& b);

namespace Visual
{
	static const COORD COORD_ZERO = { 0,0 };

	class Utils
	{
	public:
		template <typename T>
		static bool ANY(T value, std::string& out)
		{
			return true;
		}
		template<typename T, T V>
		bool TrueIfMoreV(T value, std::string& out)
		{
			if (value <= V)
				out = "Value must be more than " + std::to_string(V);

			return value > V;
		}


        static bool Question(std::string text);
		static void Out(std::string text);

		/*template <typename T>
		static T InputVar(std::string text)
		{
			Visual::TConsole* console = Visual::TConsole::GetInstance();
			COORD startPos = console->Where();
			T x;
			std::cout << text + ": ";
			std::cin >> x;

			COORD nPos = console->Where();
			console->GotoXY(startPos);
			console->DelLine(nPos.Y - startPos.Y + 1);

			return x;
		}*/

		template <class F>
		static auto bindOkFunc(F&& f)
		{
			return std::bind(f, std::placeholders::_1, std::placeholders::_2);
		}

		template <typename T>
		static T InputVar(std::string text, std::function<bool(T, std::string& out)> isOkFunc = std::bind(&ANY<T>, std::placeholders::_1, std::placeholders::_2))
		{
			Visual::TConsole* console = Visual::TConsole::GetInstance();
			COORD startPos = console->Where();

			T x;
			std::string wrongMsg = "";
			do
			{
				if (wrongMsg.size() != 0)
				{
					std::cout << wrongMsg << ", ";
				}
				std::cout << text + ": ";
				std::cin >> x;//TODO: here is a bug when expecting int but input is char

				COORD nPos = console->Where();
				console->GotoXY(startPos);
				console->DelLine(nPos.Y - startPos.Y + 1);
				wrongMsg = "";

			} while (!isOkFunc(x, wrongMsg));
			

			return x;
		}
	};

    

    
}