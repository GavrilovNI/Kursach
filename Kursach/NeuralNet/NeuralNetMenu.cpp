#pragma once
#include "NeuralNetMenu.h"
#include "Utils.h"
#include <functional>

using namespace std;
using namespace Visual;

namespace NeuralNet::NetMenu
{
	void NeuralNetMenu::createNetAction(Menu* menu)
	{
		if (menu->GetType() == "NeuralNetMenu")
		{
			NeuralNetMenu* nnMenu = (NeuralNetMenu*)menu; //dynamic_cast<NeuralNetMenu*>(menu);

			TConsole* console = TConsole::GetInstance();
			COORD startPos = console->Where();

			COORD strCOORD = startPos + COORD{ 0, (short)menu->GetButtonsCount() };
			console->GotoXY(strCOORD);
			uint32_t layersNum;
			cout << "Number of layers: ";
			cin >> layersNum;
			console->GotoXY(strCOORD);
			console->DelLine();

			vector<int> layersSizes(layersNum);

			for (size_t i = 0; i < layersNum; i++)
			{
				console->GotoXY(strCOORD);
				int layerSize;
				cout << "Size of layer #" << to_string(i) << ": ";
				cin >> layerSize;
				console->GotoXY(strCOORD);
				console->DelLine();
				layersSizes[i] = layerSize;
			}


			console->GotoXY(startPos);

			nnMenu->Create(layersSizes);
		}
	}
	void NeuralNetMenu::loadNetAction(Menu* menu)
	{
		if (menu->GetType() == "NeuralNetMenu")
		{
			NeuralNetMenu* nnMenu = (NeuralNetMenu*)menu; //dynamic_cast<NeuralNetMenu*>(menu);

			TConsole* console = TConsole::GetInstance();
			COORD startPos = console->Where();

			COORD strCOORD = startPos + COORD{ 0, (short)menu->GetButtonsCount() };
			console->GotoXY(strCOORD);
			string path;
			cout << "Path: ";
			cin >> path;
			console->GotoXY(strCOORD);
			console->DelLine();

			console->GotoXY(startPos);

			nnMenu->Load(path);
		}
	}

	const string NeuralNetMenu::loadedNetNameText = "Net Name: ";

	NeuralNetMenu::NeuralNetMenu(COORD pos, SHORT length) :Menu(pos)
	{
		function<void(Menu*)> loadAction = bind(&NeuralNetMenu::loadNetAction, this, placeholders::_1);
		function<void(Menu*)> createAction = bind(&NeuralNetMenu::createNetAction, this, placeholders::_1);

		COORD btnSize = { length,1 };
		buttonState = new Button(loadedNetNameText + "null", btnSize);
		AddButton(buttonState);
		AddButton(new ButtonAction(loadAction, "Load Net", btnSize));
		AddButton(new ButtonAction(createAction, "Create Net", btnSize));
		AddButton(new Button("Get Result", btnSize));
		AddButton(new Button("Study", btnSize));
		AddButton(new QuitButton(QuitButton::defaultName, btnSize));
	}

	string NeuralNetMenu::GetType() const
	{
		return "NeuralNetMenu";
	}

	void NeuralNetMenu::Load(string path)
	{
		UnDraw();
		buttonState->SetLabel(loadedNetNameText + path);
		Draw();

		//TODO Load
	}
	void NeuralNetMenu::Create(vector<int> layersSizes)
	{
		UnDraw();
		string name = "Net Created(";
		for (size_t i = 0; i < layersSizes.size(); i++)
		{
			name += to_string(layersSizes[i]);
			if (i != layersSizes.size() - 1)
			{
				name += ", ";
			}
		}
		name += ")";

		buttonState->SetLabel(name);

		if (_net != nullptr)
		{
			if (Visual::Utils::Question("Would you like to save previous Neural Network"))
			{
				//TODO Save
			}

			delete _net;
		}

		_net = new Net(layersSizes);

		Draw();
	}

}