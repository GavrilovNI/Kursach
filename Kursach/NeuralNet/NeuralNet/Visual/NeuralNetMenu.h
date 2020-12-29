#pragma once

#include "../../Visual/Menu.h"
#include "../Net.h"

namespace NeuralNet::NetMenu
{
	class NeuralNetMenu : Visual::Menu
	{
	private:
		void createNetAction(Menu* menu);
		void loadNetAction(Menu* menu);
		void saveNetAction(Menu* menu);

		std::string Layers2Str(const std::vector<uint32_t>& layersSizes) const;
		void UpdateNetBtn();

		bool _saved = false;
		std::string savedPath;

		template<typename T, T V>
		static bool TrueIfMoreV(T value, std::string& out)
		{
			if (value <= V)
				out = "Value must be more than " + std::to_string(V);

			return value > V;
		}

		bool isSaved() const;

	protected:
		static const std::string netNameText;
		Visual::Button* buttonState;
		NeuralNet::Net _net;

		
	public:

		NeuralNetMenu(COORD pos, SHORT length = 30);

		virtual std::string GetType() const override;

		void SaveNetIfNeeded();
		void Load();
		void Create();
		void Save();
	};
}
