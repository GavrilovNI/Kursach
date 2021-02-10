#pragma once

#include <vector>
#include <array>
#include <stdexcept>
#include <string>
#include <time.h>
#include "Matrix.h"
#include "ActivationFunc.h"

namespace NeuralNet
{
	class Layer
	{
		friend class Net;

	private:
		::Utils::Matrix<double> _weights;

	public:

		struct LayerResult
		{
			std::vector<double> inputs;
			std::vector<double> outputs;

			LayerResult(int num=0)
			{
				inputs = std::vector<double>(num);
				outputs = std::vector<double>(num);
			}

			LayerResult(std::vector<double> inputs, std::vector<double> outputs)
			{
				this->inputs = inputs;
				this->outputs = outputs;
			}

		};

		Layer(uint32_t inputsCount, uint32_t neuronsCount, int seed=time(0))
		{
			if (inputsCount == 0)
				throw std::invalid_argument("inputsCount must be more than 0");
			if (neuronsCount == 0)
				throw std::invalid_argument("neuronsCount must be more than 0");

			srand(seed);

			_weights = ::Utils::Matrix<double>(inputsCount+1, neuronsCount);//inputsCount+1 - we use move neuron? so we should add one input
		
			for (size_t y = 0; y < inputsCount+1; y++)
			{
				for (size_t x = 0; x < neuronsCount; x++)
				{
					_weights[y][x] = (rand() - RAND_MAX / 2.0) / RAND_MAX;
				}
			}

		}

		Layer(::Utils::Matrix<double> weights)
		{
			_weights = weights;
		}

		Layer(const Layer& other)
		{
			_weights = ::Utils::Matrix<double>(other._weights);
		}

		Layer& operator=(const Layer& other)
		{
			if (this == &other)
				return *this;

			_weights = other._weights;

			return *this;
		}

		bool operator==(const Layer& other)
		{
			return _weights == other._weights;
		}

		bool operator!=(const Layer& other)
		{
			return !operator==(other);
		}

		size_t GetInputsCount() const { return _weights.GetSize(0)-1; }
		size_t GetNeuronsCount() const { return _weights.GetSize(1); }

		::Utils::Matrix<double> GetWeights() const
		{
			return ::Utils::Matrix<double>(_weights);
		}

		double GetWeight(int inputIndex, int neuronIndex) const
		{
			return _weights[inputIndex][neuronIndex];
		}

		LayerResult GetResult(const std::vector<double> inputs, const ActivationFunc& func) const
		{
			if (inputs.size() != GetInputsCount())
				throw std::invalid_argument("input size is " + std::to_string(inputs.size()) + ", but expected " + std::to_string(GetInputsCount()));

			LayerResult result(GetNeuronsCount());

			for (size_t x = 0; x < GetNeuronsCount(); x++)
			{
				result.inputs[x] = 0;
				for (size_t y = 0; y < GetInputsCount(); y++)
				{
					result.inputs[x] += _weights[y][x] * inputs[y];
				}
				result.inputs[x] += _weights[GetInputsCount()][x];//using move neuron
				result.outputs[x] = func.GetResult(result.inputs[x]);
			}

			return result;
		}

	};


	class Net
	{
	private:
		std::vector<Layer> _layers;

	public:

		Net()
		{
		}

		Net(std::vector<uint32_t> layerSizes)
		{
			if (layerSizes.size() < 2)
				throw std::invalid_argument("count of layers must more than 1");

			for (size_t i = 1; i < layerSizes.size(); i++)
			{
				_layers.push_back(Layer(layerSizes[i - 1], layerSizes[i]));
			}
		}

		Net(std::vector<::Utils::Matrix<double>> layersWeights)
		{
			if (layersWeights.size() < 2)
				throw std::invalid_argument("count of layers must more than 1");

			for (size_t i = 1; i < layersWeights.size(); i++)
			{
				if (layersWeights[i - 1].GetSize(1) != layersWeights[i].GetSize(0))
					throw std::invalid_argument("layer " + std::to_string(i - 1) + " has " + std::to_string(layersWeights[i - 1].GetSize(1)) + " outputs, but layer " + std::to_string(i) + " has " + std::to_string(layersWeights[i - 1].GetSize(0)) + " inputs");
			}

			for (size_t i = 0; i < layersWeights.size(); i++)
			{
				_layers[i - 1] = Layer(layersWeights[i]);
			}
		}

		Net(std::vector<Layer> layers)
		{
			if (layers.size() == 0)
				throw std::invalid_argument("count of layers must more than 0");

			this->_layers = layers;
		}

		Net(Net& other)
		{
			_layers = other._layers;
		}

		Net& operator=(const Net& other)
		{
			_layers = other._layers;
			return *this;
		}

		bool operator==(const Net& other)
		{
			if (_layers.size() != other._layers.size())
				return false;

			for (size_t i = 0; i < _layers.size(); i++)
			{
				if (_layers[i] != other._layers[i])
					return false;
			}
			return true;
		}

		bool operator!=(const Net& other)
		{
			return !operator==(other);
		}

		int GetLayersCount() const
		{
			return _layers.size();
		}

		Layer GetLayer(uint32_t index) const
		{
			if (index >= _layers.size())
				throw std::invalid_argument("index out of range");

			return Layer(_layers[index]);
		}

		std::vector<Layer> GetLayers() const
		{
			return std::vector<Layer>(_layers);
		}

		std::vector<size_t> GetLayerSizes() const
		{
			std::vector<size_t> result(_layers.size()+1);
			if (_layers.size() > 0)
			{
				result[0] = _layers[0].GetInputsCount();
				for (size_t i = 0; i < _layers.size(); i++)
				{
					result[i+1] = _layers[i].GetNeuronsCount();
				}
			}

			return result;
		}

		size_t GetLayerSize(int layerNum) const
		{
			if (layerNum<0 || layerNum>_layers.size())
				throw std::out_of_range("LayerNum out of range.");

			if (layerNum == _layers.size())
				return _layers.rend()->GetNeuronsCount();

			return _layers[layerNum].GetInputsCount();
		}

		size_t GetInputsCount() const
		{
			return _layers[0].GetNeuronsCount();
		}

		size_t GetOutputsCount() const
		{
			return _layers.rend()->GetNeuronsCount();
		}

		std::vector<double> GetResult(const std::vector<double> inputs, const ActivationFunc& func) const
		{
			if (_layers.size() == 0)
				throw "Net not initialized";

			if (inputs.size()!=_layers[0].GetInputsCount())
				throw std::invalid_argument("input size is " + std::to_string(inputs.size()) + ", but expected " + std::to_string(_layers[0].GetInputsCount()));

			std::vector<double> result = inputs;

			for (size_t i = 0; i < _layers.size(); i++)
			{
				result = _layers[i].GetResult(result, func).outputs;
			}

			return result;
		}


		std::vector<double> Study(const std::vector<double> inputs, const std::vector<double> answers, const ActivationFunc& func, double studySpeed) const
		{
			if (inputs.size() != _layers[0].GetInputsCount())
				throw std::invalid_argument("input size is " + std::to_string(inputs.size()) + ", but expected " + std::to_string(_layers[0].GetInputsCount()));

			if (answers.size() != _layers.back().GetNeuronsCount())
				throw std::invalid_argument("answers size is " + std::to_string(answers.size()) + ", but expected " + std::to_string(_layers.back().GetNeuronsCount()));

			std::vector<Layer::LayerResult> results;
			results.push_back(Layer::LayerResult(std::vector<double>(), inputs));

			for (size_t i = 0; i < _layers.size(); i++)
			{
				results.push_back(_layers[i].GetResult(results.back().outputs, func));
			}

			//studying

			std::vector<double> errors;
			for (size_t n = 0; n < _layers.back().GetNeuronsCount(); n++)
			{
				errors.push_back(answers[n] - results.back().outputs[n]);
			}


			double errSum = 0;

			for (int l = _layers.size()-1; l >= 0; l--)
			{
				std::vector<double> newErrors(_layers[l].GetInputsCount()+1);// +1 because we use MoveNeuron
				std::fill(newErrors.begin(), newErrors.end(), 0);

				for (size_t n = 0; n < _layers[l].GetNeuronsCount(); n++)
				{
					double err = errors[n] * func.GetDerivative(results[l + 1].inputs[n]);
					for (size_t i = 0; i < _layers[l].GetInputsCount(); i++)
					{
						newErrors[i] += err * _layers[l].GetWeight(i, n);

						double wDelta = studySpeed * err * results[l].outputs[i];
						_layers[l]._weights[i][n] += wDelta;
					}

					//moveNeuron
					size_t i = _layers[l].GetInputsCount();
					newErrors[i] += err * _layers[l].GetWeight(i, n);

					double wDelta = studySpeed * err;
					_layers[l]._weights[i][n] += wDelta;

				}
				errors = newErrors;
			}


			return results.back().outputs;
		}

	};
}



