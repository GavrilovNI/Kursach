#pragma once
#include "Buttons.h"

namespace Visual
{
	class Button;
	enum class InputButton
	{
		COMMAND_KEY = 224,
		KEY_UP = 72,
		KEY_DOWN = 80,
		KEY_ENTER = 13
	};
	struct MenuSettings
	{
		bool loopScrolling = false;
	};

	class Menu
	{
	friend class MenuButton;
	private:
		COORD _pos;
	protected:
		std::vector<Button*> _buttons;
		uint32_t currButton = 0;
		bool running = false;
	public:
		MenuSettings settings;

		Menu(COORD pos);
		~Menu();

		virtual std::string GetType() const;	
		COORD GetSize() const;
		int GetButtonsCount() const;

		void AddButton(Button* button);

		void Draw() const;
		void UnDraw() const;

		void Run();
		void Stop();
	};
}
