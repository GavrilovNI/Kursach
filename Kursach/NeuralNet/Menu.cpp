#pragma once
#include "Menu.h"
#include <vector>
#include <conio.h>

using namespace std;

namespace Visual
{
	Menu::Menu(COORD pos)
	{
		this->_pos = pos;
	}
	Menu::~Menu()
	{
		UnDraw();
		for (size_t i = 0; i < _buttons.size(); i++)
		{
			delete _buttons[i];
		}
	}

	string Menu::GetType() const
	{
		return "Menu";
	}
	COORD Menu::GetSize() const
	{
		COORD result{ 0, (short)_buttons.size() };
		for (size_t i = 0; i < _buttons.size(); i++)
		{
			COORD btnSize = _buttons[i]->GetSize();
			if (result.X < btnSize.X)
				result.X = btnSize.X;
		}
		return result;
	}
	int Menu::GetButtonsCount() const
	{
		return _buttons.size();
	}

	void Menu::AddButton(Button* button)
	{
		if (_buttons.size() == 0)
		{
			button->SetPos(_pos);
		}
		else
		{
			SMALL_RECT lastButtonBounds = _buttons.back()->GetBounds();
			button->SetPos({ 0, lastButtonBounds.Bottom });
		}
		button->SetSelected(_buttons.size() == currButton);
		_buttons.push_back(button);
	}

	void Menu::Draw() const
	{
		for (size_t i = 0; i < _buttons.size(); i++)
		{
			_buttons[i]->Draw();
		}
	}
	void Menu::UnDraw() const
	{
		for (size_t i = 0; i < _buttons.size(); i++)
		{
			_buttons[i]->UnDraw();
		}
	}

	void Menu::Run()
	{
		Draw();
		running = true;
		while (running)
		{
			int input = _getch();
			if (input == (int)InputButton::COMMAND_KEY)
			{
				input = _getch();
				uint32_t newCurrButton = currButton;
				switch (input)
				{
				case (int)InputButton::KEY_DOWN:
				{
					if (_buttons.size() != 0)
					{
						if (settings.loopScrolling)
							newCurrButton = (currButton + 1) % _buttons.size();
						else
							newCurrButton = (uint32_t)fmin(currButton + 1, _buttons.size() - 1);
					}
					break;
				}
				case (int)InputButton::KEY_UP:
				{
					if (_buttons.size() != 0)
					{
						if (settings.loopScrolling)
							newCurrButton = (currButton + _buttons.size() - 1) % _buttons.size();
						else
							newCurrButton = currButton == 0 ? 0 : currButton - 1;
					}
					break;
				}
				default:
					break;
				}
				if (newCurrButton != currButton)
				{
					_buttons[currButton]->SetSelected(false);
					_buttons[newCurrButton]->SetSelected(true);
					currButton = newCurrButton;
				}
			}
			else if (input == (int)InputButton::KEY_ENTER)
			{
				if (_buttons.size() != 0)
				{
					_buttons[currButton]->Press(this);
				}
			}
		}
	}
	void Menu::Stop()
	{
		UnDraw();
		running = false;
	}

}

