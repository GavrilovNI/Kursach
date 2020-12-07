#pragma once

#include "Menu.h"
#include "Net.h"

namespace NeuralNet::NetMenu
{
	class NeuralNetMenu : Visual::Menu
	{
	private:
		void createNetAction(Menu* menu);
		void loadNetAction(Menu* menu);
	protected:
		static const std::string loadedNetNameText;
		Visual::Button* buttonState;
		NeuralNet::Net* _net = nullptr;
	public:

		NeuralNetMenu(COORD pos, SHORT length = 20);

		virtual std::string GetType() const override;

		void Load(std::string path);
		void Create(std::vector<int> layersSizes);
	};
}
