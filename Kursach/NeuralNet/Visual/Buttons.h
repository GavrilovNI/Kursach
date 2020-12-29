#pragma once
#include "TConsole.h"
#include "Utils.h"
#include <functional>

namespace Visual
{
	class Menu;

	struct ButtonSettings
	{
		ColorSettings _active = {
			Color::BLACK,
			Color::WHITE,
		};
		ColorSettings inactive = {
			Color::BLACK,
			Color::DARKGRAY
		};
		ColorSettings activeSelected = {
			Color::WHITE,
			Color::BLACK,
		};
		ColorSettings inactiveSelected{
			Color::DARKGRAY,
			Color::BLACK
		};
	};

	class Button
	{
	private:

		std::string _label;
		COORD _pos{ 0,0 };
		COORD _size{ 0,0 };

		bool _active = true;
		bool _drawed = false;
		bool _selected = false;
	protected:

		virtual void OnPressed(Menu* menu) { }

		void ApplySettingsToConsole() const;
		void DrawBackground() const;
		void DrawLabel() const;
		ButtonSettings _settings;

	public:


		
		Button(std::string label = "", COORD size = COORD_ZERO, COORD pos = COORD_ZERO);

		virtual std::string GetType() const;

		SMALL_RECT GetBounds() const;
		bool IsActive();
		void SetActive(bool value);
		bool IsSelected();
		void SetSelected(bool value);
		void SetLabel(std::string label);
		std::string Getlabel();
		void SetSize(COORD size);
		COORD GetSize() const;
		void SetPos(COORD pos);
		COORD GetPos() const;
		ButtonSettings GetSettings() const;
		void SetSettings(ButtonSettings settings);

		bool Press(Menu* menu);

		void Draw();
		void UnDraw();

	};


	class QuitButton : public Button
	{
		friend class MenuButton;
	protected:
		Menu* _menu = nullptr;
	public:
		static const std::string defaultName;

		QuitButton(std::string label = defaultName, COORD size = COORD_ZERO, COORD pos = COORD_ZERO) :Button(label, size, pos) { }

		virtual std::string GetType() const override;
		virtual void OnPressed(Menu* menu) override;
	};


	class MenuButton : public Button
	{
	protected:
		Menu* _menu;
	public:

		MenuButton(Menu* menu, std::string label = "", COORD size = COORD_ZERO, COORD pos = COORD_ZERO);

		virtual std::string GetType() const override;
		virtual void OnPressed(Menu* menu) override;
	};

	class ButtonAction : public Button
	{
	protected:
		std::function<void(Menu*)> _action;
	public:

		ButtonAction(std::function<void(Menu*)> action, std::string label = "", COORD size = COORD_ZERO, COORD pos = COORD_ZERO);

		virtual std::string GetType() const override;
		virtual void OnPressed(Menu* menu)override;
	};
}

