#pragma once
#include <cmath>

namespace NeuralNet
{
	class ActivationFunc
	{

	public:
		virtual double GetResult(double value) const = 0;
		virtual double GetDerivative(double value) const = 0;

	};

	class Sigmoid : public ActivationFunc
	{

	public:
		virtual double GetResult(double value) const override
		{
			return 1.0 / (1.0 + exp(-value));
		}
		virtual double GetDerivative(double value) const override
		{
			double result = GetResult(value);
			return result * (1.0 - result);
		}

	};

	class BipolarSigmoid : public ActivationFunc
	{

	public:
		virtual double GetResult(double value) const override
		{
			return 2.0 / (1.0 + exp(-value)) - 1.0;
		}
		virtual double GetDerivative(double value) const override
		{
			double result = GetResult(value);
			return 0.5 * (1.0 - result * result);
		}

	};
}