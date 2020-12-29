#pragma once
#include "Buttons.h"
#include "Menu.h"
#include <string>
#include <iostream>

using namespace std;

namespace Visual
{

	void Button::ApplySettingsToConsole() const
	{
		TConsole* console = TConsole::GetInstance();
		ConsoleSettings newSettings = console->GetSettings();
		if (_active)
		{
			newSettings.color = (_selected ? _settings.activeSelected : _settings._active);
		}
		else
		{
			newSettings.color = (_selected ? _settings.inactiveSelected : _settings.inactive);
		}
		console->SetSettings(newSettings);
	}
	
	
	Button::Button(string label, COORD size, COORD pos)
	{
		this->_label = label;
		this->_size = size;
		this->_pos = pos;
	}
	string Button::GetType() const
	{
		return "Button";
	}
	SMALL_RECT Button::GetBounds() const
	{
		return { _pos.X, _pos.Y, _pos.X + _size.X, _pos.Y + _size.Y };
	}
	bool Button::IsActive()
	{
		return _active;
	}
	void Button::SetActive(bool value)
	{
		_active = value;
		if (_drawed)
			Draw();
	}
	bool Button::IsSelected()
	{
		return _selected;
	}
	void Button::SetSelected(bool value)
	{
		_selected = value;
		if (_drawed)
			Draw();
	}
	void Button::SetLabel(string label)
	{
		this->_label = label;
		if (_drawed)
			Draw();
	}
	string Button::Getlabel()
	{
		return _label;
	}
	void Button::SetSize(COORD size)
	{
		this->_size = size;
		if (_drawed)
			Draw();
	}
	COORD Button::GetSize() const
	{
		return _size;
	}
	void Button::SetPos(COORD pos)
	{
		if (_drawed)
			UnDraw();
		this->_pos = pos;
		if (_drawed)
			Draw();
	}
	COORD Button::GetPos() const
	{
		return _pos;
	}
	ButtonSettings Button::GetSettings() const
	{
		return _settings;
	}
	void Button::SetSettings(ButtonSettings settings)
	{
		this->_settings = _settings;
		if (_drawed)
			Draw();
	}
	
	bool Button::Press(Menu* menu)
	{
		if (_active)
			OnPressed(menu);

		return _active;
	}	
	
	void Button::DrawBackground() const
	{
		TConsole* console = TConsole::GetInstance();
		ConsoleSettings prevSettings = console->GetSettings();
		ApplySettingsToConsole();
		console->Fill(GetBounds(), ' ');
		console->SetSettings(prevSettings);
	}
	void Button::DrawLabel() const
	{
		TConsole* console = TConsole::GetInstance();
		COORD prevPos = console->Where();
		ConsoleSettings prevSettings = console->GetSettings();

		ApplySettingsToConsole();

		console->GotoXY(_pos);
		cout << _label.substr(0, _size.X);

		console->SetSettings(prevSettings);
		console->GotoXY(prevPos);
	}
	void Button::Draw()
	{
		DrawBackground();
		DrawLabel();
		_drawed = true;
	}
	void Button::UnDraw()
	{
		TConsole::GetInstance()->Fill(GetBounds(), ' ');
		_drawed = false;
	}


	const string QuitButton::defaultName = "quit";
	string QuitButton::GetType() const 
	{
		return "QuitButton";
	}
	void QuitButton::OnPressed(Menu* menu)
	{
		menu->Stop();
		if (_menu != nullptr)
		{
			Menu* tmp = _menu;
			_menu = nullptr;
			tmp->Draw();
		}
	}




	MenuButton::MenuButton(Menu* menu, string label, COORD size, COORD pos) :Button(label, size, pos)
	{
		this->_menu = menu;
	}
	string MenuButton::GetType() const
	{
		return "MenuButton";
	}
	void MenuButton::OnPressed(Menu* menu)
	{
		menu->UnDraw();

		for (size_t i = 0; i < _menu->_buttons.size(); i++)
		{
			if (_menu->_buttons[i]->GetType() == "QuitButton")
			{
				QuitButton* quitButton = (QuitButton*)_menu->_buttons[i]; //dynamic_cast<QuitButton*>(_menu->_buttons[i]);

				quitButton->_menu = menu;
			}

		}

		_menu->Run();
	}

	



	ButtonAction::ButtonAction(function<void(Menu*)> action, string label, COORD size, COORD pos) :Button(label, size, pos)
	{
		this->_action = action;
	}
	string ButtonAction::GetType() const
	{
		return "QuitButton";
	}
	void ButtonAction::OnPressed(Menu* menu)
	{
		if (_action != nullptr)
		{
			_action(menu);
		}
	}
	
}
