#pragma once
#include "Net.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

namespace NeuralNet::Utils
{
	class Loader
	{
	private:

		template <typename T>
		static void Write2Stream(T value, std::ostream& stream)
		{
			stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
		}

		static void SaveLayer(const Layer layer, std::ostream& stream)
		{
			Write2Stream(layer.GetInputsCount(), stream);
			Write2Stream(layer.GetNeuronsCount(), stream);

			::Utils::Matrix<double> sinapses = layer.GetWeights();

			for (size_t i = 0; i < layer.GetInputsCount()+1; i++)//+1 because we use move neuron
			{
				for (size_t n = 0; n < layer.GetNeuronsCount(); n++)
				{
					Write2Stream(sinapses[i][n], stream);
				}
			}
		}

		static Layer LoadLayer(std::istream& stream)
		{
			size_t inputsCount;
			size_t neuronsCount;
			stream.read(reinterpret_cast<char*>(&inputsCount), sizeof(inputsCount));
			stream.read(reinterpret_cast<char*>(&neuronsCount), sizeof(neuronsCount));

			::Utils::Matrix<double> sinapses(inputsCount+1, neuronsCount);//+1 because we use move neuron

			for (size_t i = 0; i < inputsCount+1; i++)//+1 because we use move neuron
			{
				for (size_t n = 0; n < neuronsCount; n++)
				{
					stream.read(reinterpret_cast<char*>(&sinapses[i][n]), sizeof(sinapses[i][n]));
				}
			}

			return Layer(sinapses);
		}

		static bool FileExist(std::string path)
		{
			struct stat buf;
			return stat(path.c_str(), &buf) != -1;
		}

	public:

		static bool Save(const Net& net, std::string path, bool rewrite = false)
		{
			if (FileExist(path) && !rewrite)
			{
				return false;
			}

			std::ofstream stream(path, std::ios::out | std::ios::binary | std::ios::trunc);

			Save(net, stream);
			stream.close();

			return true;
		}

		static void Save(const Net& net, std::ostream& stream)
		{
			size_t layersCount = net.GetLayersCount();
			Write2Stream(layersCount, stream);

			for (size_t i = 0; i < layersCount; i++)
			{
				SaveLayer(net.GetLayer(i), stream);
			}
		}

		static bool Load(std::string path, Net& net)
		{
			if (!FileExist(path))
			{
				return false;
			}

			std::ifstream stream(path, std::ios::in | std::ios::binary | std::ios::app);
			net = Load(stream);
			stream.close();

			return true;
		}

		static Net Load(std::istream& stream)
		{
			size_t layersCount;
			stream.read(reinterpret_cast<char*>(&layersCount), sizeof(layersCount));

			std::vector<Layer> layers;

			for (size_t i = 0; i < layersCount; i++)
			{
				layers.push_back(LoadLayer(stream));
			}

			return Net(layers);
		}

	};
	
}