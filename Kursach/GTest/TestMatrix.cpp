#pragma once
#include "gtest/gtest.h"
#include "../NeuralNet/Matrix.h"

using namespace NeuralNet::Utils;

TEST(Matrix, SizeConstructor)
{
	
	EXPECT_NO_THROW(Matrix<int>(2, 3));
	EXPECT_NO_THROW(Matrix<float>(2, 3));
}

TEST(Matrix, ZeroSize)
{
	EXPECT_NO_THROW(Matrix<int>(0,0));
	EXPECT_NO_THROW(Matrix<int>(0,4));
	EXPECT_NO_THROW(Matrix<int>(3,0));

	Matrix<int> m(0,0);

	EXPECT_EQ(m.GetSize(0), 0);
	EXPECT_EQ(m.GetSize(1), 0);
}

TEST(Matrix, GetSize)
{
	Matrix<int> m(2, 3);
	EXPECT_NO_THROW(m.GetSize(0));
	EXPECT_NO_THROW(m.GetSize(1));
	EXPECT_ANY_THROW(m.GetSize(2));

	EXPECT_EQ(m.GetSize(0), 2);
	EXPECT_EQ(m.GetSize(1), 3);
}

TEST(Matrix, IndexOperator)
{
	Matrix<int> m(2, 3);

	for (size_t y = 0; y < m.GetSize(0); y++)
	{
		for (size_t x = 0; x < m.GetSize(1); x++)
		{
			EXPECT_NO_THROW(m[y][x] = y * m.GetSize(1) + x);
		}
	}

	for (size_t y = 0; y < m.GetSize(0); y++)
	{
		for (size_t x = 0; x < m.GetSize(1); x++)
		{
			EXPECT_EQ(m[y][x], y * m.GetSize(1) + x);
		}
	}
}


TEST(Matrix, CopyConstructor)
{
	Matrix<int> m(2, 3);

	for (size_t y = 0; y < m.GetSize(0); y++)
	{
		for (size_t x = 0; x < m.GetSize(1); x++)
		{
			EXPECT_NO_THROW(m[y][x] = y * m.GetSize(1) + x);
		}
	}

	EXPECT_NO_THROW(Matrix<int> m2(m));

	Matrix<int> m2(m);

	EXPECT_EQ(m.GetSize(0), m2.GetSize(0));
	EXPECT_EQ(m.GetSize(1), m2.GetSize(1));

	for (size_t y = 0; y < m.GetSize(0); y++)
	{
		for (size_t x = 0; x < m.GetSize(1); x++)
		{
			EXPECT_NO_THROW(m2[y][x]);
			EXPECT_EQ(m[y][x], m2[y][x]);
			m[y][x] = -1;
			EXPECT_NE(m[y][x], m2[y][x]);
			EXPECT_EQ(m2[y][x], y * m.GetSize(1) + x);
		}
	}
}