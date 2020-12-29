#pragma once
#include "gtest/gtest.h"
#include "../NeuralNet/NeuralNet/Net.h"
#include "../NeuralNet/NeuralNet/ActivationFunc.h"
#include <vector>

using namespace NeuralNet;
using namespace std;


TEST(Layer, Constructor)
{
	EXPECT_NO_THROW(Layer layer(5, 4));
	EXPECT_ANY_THROW(Layer layer(0, 4));
	EXPECT_ANY_THROW(Layer layer(5, 0));
}

TEST(Layer, GetInputsCount)
{
	Layer layer(5, 4);
	EXPECT_NO_THROW(layer.GetInputsCount());
	EXPECT_EQ(layer.GetInputsCount(), 5);
}

TEST(Layer, GetNeuronsCount)
{
	Layer layer(5, 4);
	EXPECT_NO_THROW(layer.GetNeuronsCount());
	EXPECT_EQ(layer.GetNeuronsCount(), 4);
}

TEST(Layer, GetResultWorks)
{
	Layer layer(5, 4);
	EXPECT_NO_THROW(layer.GetResult({1, 2, 3, 4, 3.5}, NeuralNet::Sigmoid()));
	EXPECT_ANY_THROW(layer.GetResult({1, 2, 3, 4}, NeuralNet::Sigmoid()));

	auto result = layer.GetResult({ 1, 2, 3, 4, 3 }, NeuralNet::Sigmoid());

	EXPECT_EQ(result.inputs.size(), 4);
	EXPECT_EQ(result.outputs.size(), 4);

	for (size_t i = 0; i < result.inputs.size(); i++)
	{
		EXPECT_EQ(result.outputs[i], NeuralNet::Sigmoid().GetResult(result.inputs[i]));
	}
}



TEST(NeuralNet, ConstructorFromLayerSizes)
{
	EXPECT_NO_THROW(Net net(vector<uint32_t>{ 16, 5, 4, 2 }));

}

TEST(NeuralNet, ConstructorDefault)
{
	EXPECT_NO_THROW(Net net);
	Net net;
	EXPECT_EQ(net.GetLayersCount(), 0);
	EXPECT_ANY_THROW(net.GetLayer(0));
	EXPECT_ANY_THROW(net.GetResult({1,2,3}, NeuralNet::Sigmoid()));
}

TEST(NeuralNet, LayersConstructor_minCountOfLayersIs2)
{
	EXPECT_NO_THROW(Net net(vector<uint32_t>{ 16, 5 }));
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ 16 }));
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ }));
}

TEST(NeuralNet, LayersConstructor_AnyLayerSizeMoreZero)
{
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ 16, 3, 0, 4 }));
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ 0, 3, 1, 4 }));
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ 4, 3, 1, 0 }));
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ 16, 0 }));
	EXPECT_ANY_THROW(Net net(vector<uint32_t>{ 0 }));
}

TEST(NeuralNet, GetLayersCount)
{
	Net net(vector<uint32_t>{ 16, 3, 2, 4 });
	EXPECT_NO_THROW(net.GetLayersCount());
	EXPECT_EQ(net.GetLayersCount(), 3);
}

TEST(NeuralNet, LayersBuildedRight)
{
	vector<uint32_t> vec{ 16, 3, 2, 4 };
	Net net(vec);
	
	for (size_t i = 0; i < net.GetLayersCount(); i++)
	{
		Layer layer = net.GetLayer(i);

		EXPECT_EQ(layer.GetInputsCount(), vec[i]);
		EXPECT_EQ(layer.GetNeuronsCount(), vec[i+1]);
	}
}









