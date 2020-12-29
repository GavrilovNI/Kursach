#pragma once

#include "gtest/gtest.h"
#include "../NeuralNet/NeuralNet/Net.h"
#include "../NeuralNet/NeuralNet/NetLoader.h"
#include "../NeuralNet/NeuralNet/ActivationFunc.h"
#include <sstream>
#include <vector>


using namespace NeuralNet;
using namespace NeuralNet::Utils;
using namespace std;

/*
#pragma warning(disable:C2296)
template <typename T>
std::vector<unsigned char> Var2Bytes(T value)
{
	std::vector<unsigned char> arrayOfByte(sizeof(value));
	for (int i = 0; i < sizeof(value); i++)
		arrayOfByte[i] = (value >> (i * 8));
	return arrayOfByte;
}
#pragma warning(default:C2296) 
*/

template <typename T>
std::vector<char> Var2Bytes(T value)
{
	std::vector<char> arrayOfByte(sizeof(value));
	char* val = reinterpret_cast<char*>(&value);
	for (int i = 0; i < sizeof(value); i++)
		arrayOfByte[i] = *(val + i);
	return arrayOfByte;
}


template <typename T>
void AddVector2Another(std::vector<T>& dest, std::vector<T> from)
{
	dest.insert(dest.end(), from.begin(), from.end());
}


TEST(NetLoader, SaveWorksRight)
{
	std::ostringstream buf;

	auto layerSizes = vector<uint32_t>{ 5, 4, 4, 2 };

	Net net(layerSizes);
	ASSERT_NO_THROW(Loader::Save(net, buf));

	auto vec = Var2Bytes(layerSizes.size()-1);
	
	for (size_t l = 0; l < layerSizes.size()-1; l++)
	{
		AddVector2Another(vec, Var2Bytes(layerSizes[l]));
		AddVector2Another(vec, Var2Bytes(layerSizes[l+1]));

		Layer layer = net.GetLayer(l);
		for (size_t i = 0; i < layer.GetInputsCount()+1; i++)//+1 because we use move neuron
		{
			for (size_t n = 0; n < layer.GetNeuronsCount(); n++)
			{
				AddVector2Another(vec, Var2Bytes(layer.GetWeight(i,n)));
			}
		}
	}

	string str = buf.str();
	ASSERT_EQ(str.size(), vec.size());

	for (size_t i = 0; i < str.size(); i++)
	{
		ASSERT_EQ(str[i], vec[i]);
	}

}



TEST(NetLoader, LoadWorksRight)
{
	std::stringstream buf;

	auto layerSizes = vector<uint32_t>{ 5, 4, 4, 2 };

	Net net(layerSizes);
	Loader::Save(net, buf);
	Net net2;
	ASSERT_NO_THROW( net2 = Loader::Load(buf));

	ASSERT_EQ(net.GetLayersCount(), net2.GetLayersCount());
	for (size_t i = 0; i < net.GetLayersCount(); i++)
	{
		Layer layer = net.GetLayer(i);
		Layer layer2 = net2.GetLayer(i);

		ASSERT_EQ(layer.GetInputsCount(), layer2.GetInputsCount());
		ASSERT_EQ(layer.GetNeuronsCount(), layer2.GetNeuronsCount());

		for (size_t i = 0; i < layer.GetInputsCount()+1; i++)
		{
			for (size_t n = 0; n < layer.GetNeuronsCount(); n++)
			{
				ASSERT_EQ(layer.GetWeight(i,n), layer2.GetWeight(i, n));
			}
		}
	}
}



