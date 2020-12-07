#pragma once
#include "Net.h"
#include <fstream>
#include <string>

namespace NeuralNet::Utils
{
	class Loader
	{
	private:

		static void Save(const Layer layer, std::ofstream& stream)
		{
			stream.write(reinterpret_cast<const char*>(layer.GetInputsCount()), sizeof(layer.GetInputsCount()));
			stream.write(reinterpret_cast<const char*>(layer.GetNeuronsCount()), sizeof(layer.GetNeuronsCount()));

			Utils::Matrix<double> sinapses = layer.GetWeights();

			for (size_t y = 0; y < layer.GetInputsCount(); y++)
			{
				for (size_t x = 0; x < layer.GetNeuronsCount(); x++)
				{
					stream.write(reinterpret_cast<const char*>(&sinapses[y][x]), sizeof(sinapses[y][x]));
				}
			}
		}

		static Layer LoadLayer(std::ifstream& stream)
		{
			size_t inputsCount;
			size_t neuronsCount;
			stream.read(reinterpret_cast<char*>(&inputsCount), sizeof(inputsCount));
			stream.read(reinterpret_cast<char*>(&neuronsCount), sizeof(neuronsCount));

			Utils::Matrix<double> sinapses(inputsCount, neuronsCount);

			for (size_t y = 0; y < inputsCount; y++)
			{
				for (size_t x = 0; x < neuronsCount; x++)
				{
					stream.read(reinterpret_cast<char*>(&sinapses[y][x]), sizeof(sinapses[y][x]));
				}
			}

			return Layer(sinapses);
		}


	public:

		static void Save(const Net net, std::string path)
		{
			std::ofstream stream(path, std::ios::out | std::ios::binary | std::ios::app);

			size_t layersCount = net.GetLayersCount();
			stream.write(reinterpret_cast<const char*>(&layersCount), sizeof(layersCount));

			for (size_t i = 0; i < layersCount; i++)
			{
				Save(net.GetLayer(i), stream);
			}

			stream.close();
		}

		static Net* LoadNet(std::string path)
		{
			std::ifstream stream(path, std::ios::in | std::ios::binary | std::ios::app);

			size_t layersCount;
			stream.read(reinterpret_cast<char*>(&layersCount), sizeof(layersCount));

			std::vector<Layer> layers;

			for (size_t i = 0; i < layersCount; i++)
			{
				layers.push_back(LoadLayer(stream));
			}

			stream.close();

			return new Net(layers);
		}

	};
	
}