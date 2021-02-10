#pragma once
#include <map>
#include <iostream>
#include "Net.h"
#include "../Imaging/Image.h"

namespace NeuralNet
{
	struct Size
	{
		int width, height;

		Size(int width, int height)
		{
			this->width = width;
			this->height = height;
		}

		Size() : Size(0, 0)
		{
		}
	};

	struct Point
	{
		int x, y;

		Point(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		Point() : Point(0,0)
		{
		}
	};

	class TrainData
	{
	public:
		Size _dataSize;
		uint32_t _outputsCount;
		std::map<Point, std::vector<double>> _data;

		TrainData(std::istream stream)
		{
			stream >> _dataSize.width;
			stream >> _dataSize.height;
			stream >> _outputsCount;
			int count;
			stream >> count;
			for (size_t i = 0; i < count; i++)
			{
				Point p;
				stream >> p.x;
				stream >> p.y;

				auto outs = std::vector<double>(_outputsCount);
				for (size_t o = 0; o < _outputsCount; o++)
				{
					stream >> outs[o];
				}

				_data[p] = outs;
			}
		}
	};


	class Trainer
	{
	public:

		std::vector<double> GetInputs_OnlyR(const Imaging::Image* image, Point startPoint, Size dataSize)
		{
			std::vector<double> result(dataSize.width * dataSize.height);
			int i = 0;
			for (size_t y = startPoint.y; y < dataSize.height + startPoint.y; y++)
			{
				for (size_t x = startPoint.x; x < dataSize.width + startPoint.x; x++)
				{
					result[i] = (*image)[y][x].r;
					i++;
				}
			}

			return result;
		}

		void Train(Net* net, TrainData* data, const Imaging::Image* image, ActivationFunc activationFunc, double studySpeed)
		{
			if (net->GetInputsCount() != data->_dataSize.width * data->_dataSize.height)
				throw std::invalid_argument("Wrong data inputs count.");

			if (net->GetOutputsCount() != data->_outputsCount)
				throw std::invalid_argument("Wrong data outputs count.");

			for (auto it = data->_data.begin(); it!=data->_data.end(); ++it)
			{
				auto inputs = GetInputs_OnlyR(image, it->first, data->_dataSize);
				net->Study(inputs, it->second, activationFunc, studySpeed);
			}
		}

	};
}
