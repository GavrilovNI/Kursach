#pragma once
#include "NeuralNetMenu.h"
#include "Utils.h"
#include "NetLoader.h"
#include <functional>
#include <string>

using namespace std;
using namespace Visual;
using namespace NeuralNet;
using namespace NeuralNet::Utils;

namespace NeuralNet::NetMenu
{
	void NeuralNetMenu::SaveNetIfNeeded()
	{
		if (_net.GetLayersCount() == 0 || isSaved())
			return;

		TConsole* console = TConsole::GetInstance();
		COORD startPos = console->Where();

		SetCursorUnderMenu();

		if (Visual::Utils::Question("Would you like to save previous Neural Network"))
		{
			Save();
		}
		console->GotoXY(startPos);
	}

	void NeuralNetMenu::createNetAction(Menu* menu)
	{
		if (menu->GetType() == "NeuralNetMenu")
		{
			NeuralNetMenu* nnMenu = (NeuralNetMenu*)menu; //dynamic_cast<NeuralNetMenu*>(menu);

			nnMenu->SaveNetIfNeeded();
			nnMenu->Create();
		}
	}
	void NeuralNetMenu::loadNetAction(Menu* menu)
	{
		if (menu->GetType() == "NeuralNetMenu")
		{
			NeuralNetMenu* nnMenu = (NeuralNetMenu*)menu; //dynamic_cast<NeuralNetMenu*>(menu);

			nnMenu->SaveNetIfNeeded();
			nnMenu->Load();
		}
	}
	void NeuralNetMenu::saveNetAction(Menu* menu)
	{
		if (menu->GetType() == "NeuralNetMenu")
		{
			NeuralNetMenu* nnMenu = (NeuralNetMenu*)menu; //dynamic_cast<NeuralNetMenu*>(menu);

			nnMenu->Save();
		}
	}

	const string NeuralNetMenu::netNameText = "Net ";

	NeuralNetMenu::NeuralNetMenu(COORD pos, SHORT length) :Menu(pos)
	{
		function<void(Menu*)> loadAction = bind(&NeuralNetMenu::loadNetAction, this, placeholders::_1);
		function<void(Menu*)> createAction = bind(&NeuralNetMenu::createNetAction, this, placeholders::_1);
		function<void(Menu*)> saveAction = bind(&NeuralNetMenu::saveNetAction, this, placeholders::_1);

		COORD btnSize = { length,1 };
		buttonState = new Button(netNameText, btnSize);
		AddButton(buttonState);
		AddButton(new ButtonAction(createAction, "Create Net", btnSize));
		AddButton(new ButtonAction(loadAction, "Load Net", btnSize));
		AddButton(new ButtonAction(saveAction, "Save Net", btnSize));
		AddButton(new Button("Get Result", btnSize));
		AddButton(new Button("Study", btnSize));
		AddButton(new QuitButton(QuitButton::defaultName, btnSize));
	}


	string NeuralNetMenu::GetType() const
	{
		return "NeuralNetMenu";
	}

	string NeuralNetMenu::Layers2Str(const vector<uint32_t>& layersSizes) const
	{
		string result = "(";
		for (size_t i = 0; i < layersSizes.size(); i++)
		{
			result += to_string(layersSizes[i]);
			if (i != layersSizes.size() - 1)
			{
				result += ", ";
			}
		}
		result += ")";
		return result;
	}

	bool NeuralNetMenu::isSaved() const
	{
		if (!_saved)
			return false;
		Net net;
		if (!Loader::Load(savedPath, net))
			return false;

		return net == _net;
	}

	void NeuralNetMenu::UpdateNetBtn()
	{
		UnDraw();
		buttonState->SetLabel(netNameText + Layers2Str(_net.GetLayerSizes()));
		Draw();
	}

	void NeuralNetMenu::Load()
	{
		TConsole* console = TConsole::GetInstance();
		COORD startPos = console->Where();
		SetCursorUnderMenu();
		string path = Visual::Utils::InputVar<string>("Load path");

		bool loaded = Loader::Load(path, _net);
		if (loaded)
		{
			UpdateNetBtn();
			savedPath = path;
			_saved = true;
		}

		Visual::Utils::Out(loaded ? "loaded" : "file not found");

		console->GotoXY(startPos);
	}



	
	

	void NeuralNetMenu::Create()
	{
		TConsole* console = TConsole::GetInstance();
		COORD startPos = console->Where();
		SetCursorUnderMenu();

		//auto more0 = std::bind(&TrueIfMoreV<uint32_t, 0>, std::placeholders::_1, std::placeholders::_2);
		auto more0 = Visual::Utils::bindOkFunc(&TrueIfMoreV<uint32_t, 0>);//TODO: use not memver function

		uint32_t layersNum = Visual::Utils::InputVar<uint32_t>("Number of layers", more0);
		vector<uint32_t> layersSizes(layersNum+1);

		layersSizes[0] = Visual::Utils::InputVar<uint32_t>("Size of inputs", more0);
		for (size_t i = 0; i < layersNum; i++)
		{
			layersSizes[i + 1] = Visual::Utils::InputVar<uint32_t>("Size of layer #" + to_string(i), more0);
		}

		_net = Net(layersSizes);

		UpdateNetBtn();

		Visual::Utils::Out("created");
		console->GotoXY(startPos);

		_saved = false;
	}

	void NeuralNetMenu::Save()
	{
		if (_net.GetLayersCount() == 0)
			return;

		TConsole* console = TConsole::GetInstance();
		COORD startPos = console->Where();
		SetCursorUnderMenu();
		string path = Visual::Utils::InputVar<string>("Save path");
		bool saved = Loader::Save(_net, path);
		if (!saved)
		{
			if (Visual::Utils::Question("File already exist, do you want to rewrite it"))
			{
				saved = Loader::Save(_net, path, true);
			}
		}


		Visual::Utils::Out(saved ? "saved" : "not saved");
		console->GotoXY(startPos);

		savedPath = path;
		_saved = saved;
	}

}