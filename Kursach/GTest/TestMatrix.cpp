#pragma once
#include "gtest/gtest.h"
#include "../NeuralNet/NeuralNet/Matrix.h"

using namespace Utils;

TEST(Matrix, SizeConstructor)
{
	
	EXPECT_NO_THROW(Matrix<int>(2, 3));
	EXPECT_NO_THROW(Matrix<float>(2, 3));
}
TEST(Matrix, Initializer_list_Constructor)
{
	try
	{
		Matrix<int> a = { {1,2,3},{4,5,6} };

		for (size_t i1 = 0; i1 < 2; i1++)
		{
			for (size_t i2 = 0; i2 < 3; i2++)
			{
				ASSERT_NO_THROW(a[i1][i2]);
			}
		}

		ASSERT_EQ(a[0][0], 1);
		ASSERT_EQ(a[0][1], 2);
		ASSERT_EQ(a[0][2], 3);
		ASSERT_EQ(a[1][0], 4);
		ASSERT_EQ(a[1][1], 5);
		ASSERT_EQ(a[1][2], 6);

	}
	catch (...)
	{
		ASSERT_TRUE(false);
	}
}
TEST(Matrix, Initializer_list_Constructor_notfull)
{
	try
	{
		Matrix<int> a = { {1,2},{4,5,6} };

		for (size_t i1 = 0; i1 < 2; i1++)
		{
			for (size_t i2 = 0; i2 < 3; i2++)
			{
				ASSERT_NO_THROW(a[i1][i2]);
			}
		}

		ASSERT_EQ(a[0][0], 1);
		ASSERT_EQ(a[0][1], 2);
		ASSERT_EQ(a[1][0], 4);
		ASSERT_EQ(a[1][1], 5);
		ASSERT_EQ(a[1][2], 6);

	}
	catch (...)
	{
		ASSERT_TRUE(false);
	}
}
TEST(Matrix, Initializer_list_Constructor_notfull2)
{
	try
	{
		Matrix<int> a = { {},{4,5,6} };

		for (size_t i1 = 0; i1 < 2; i1++)
		{
			for (size_t i2 = 0; i2 < 3; i2++)
			{
				ASSERT_NO_THROW(a[i1][i2]);
			}
		}

		ASSERT_EQ(a[1][0], 4);
		ASSERT_EQ(a[1][1], 5);
		ASSERT_EQ(a[1][2], 6);

	}
	catch (...)
	{
		ASSERT_TRUE(false);
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

TEST(Matrix, OperatorEqual)
{
	Matrix<int> a = { {1,2,3},{4,5,6} };
	Matrix<int> b = { {1,2,3},{4,5,6} };
	Matrix<int> c = { {1,2,3},{4,5,6},{4,5,6} };
	Matrix<int> e = { {1,2},{3,4},{5,6} };
	Matrix<int> d = { {1,2,3},{4,7,6} };

	ASSERT_NO_THROW(a == a);
	ASSERT_NO_THROW(a == b);
	ASSERT_NO_THROW(a == c);
	ASSERT_NO_THROW(a == d);
	ASSERT_NO_THROW(a == e);
	ASSERT_NO_THROW(a != a);
	ASSERT_NO_THROW(a != b);
	ASSERT_NO_THROW(a != c);
	ASSERT_NO_THROW(a != d);
	ASSERT_NO_THROW(a != e);
	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a != b);
	ASSERT_TRUE(a == a);
	ASSERT_FALSE(a != a);
	ASSERT_FALSE(a == c);
	ASSERT_TRUE(a != c);
	ASSERT_FALSE(a == d);
	ASSERT_TRUE(a != d);
	ASSERT_TRUE(a != e);
	ASSERT_FALSE(a == e);

}

TEST(Matrix, OperatorCopy)
{
	Matrix<int> m = { {1,2,3},{4,5,6} };
	Matrix<int> m2;

	EXPECT_NO_THROW(m2 = m);
	EXPECT_TRUE(m == m2);
	
}
TEST(Matrix, OperatorCopy_MatrixHasSameSize)
{
	Matrix<int> m = { {1,2,3},{4,5,6} };
	Matrix<int> m2 = { {7,8},{9,10},{11,12} };
	Matrix<int> m3 = { {7,8,9},{10,11,12} };

	EXPECT_NO_THROW(m2 = m);
	EXPECT_NO_THROW(m3 = m);
	EXPECT_TRUE(m == m2);
	EXPECT_TRUE(m == m3);
}

TEST(Matrix, OperatorIndex)
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


TEST(Matrix, RotateR)
{
	//1 2 3
	//4 5 6

	//4 1
	//5 2
	//6 3

	Matrix<int> a = { {1,2,3},{4,5,6} };
	Matrix<int> r = { {4,1},{5,2},{6,3} };

	ASSERT_NO_THROW(a.RotateR());
	ASSERT_TRUE(a.RotateR() == r);

}
TEST(Matrix, RotateL)
{
	//1 2 3
	//4 5 6

	//3 6
	//2 5
	//1 4

	Matrix<int> a = { {1,2,3},{4,5,6} };
	Matrix<int> r = { {3,6},{2,5},{1,4} };

	ASSERT_NO_THROW(a.RotateL());
	ASSERT_TRUE(a.RotateL() == r);

}
TEST(Matrix, Rotate180)
{
	//1 2 3
	//4 5 6

	//6 5 4
	//3 2 1

	Matrix<int> a = { {1,2,3},{4,5,6} };
	Matrix<int> r = { {6,5,4},{3,2,1} };

	ASSERT_NO_THROW(a.Rotate180());
	ASSERT_TRUE(a.Rotate180() == r);

}
TEST(Matrix, SwapLR)
{
	//1 2 3
	//4 5 6

	//3 2 1
	//6 5 4

	Matrix<int> a = { {1,2,3},{4,5,6} };
	Matrix<int> r = { {3,2,1},{6,5,4} };

	ASSERT_NO_THROW(a.SwapLR());
	ASSERT_TRUE(a.SwapLR() == r);

}
TEST(Matrix, SwapUD)
{
	//1 2 3
	//4 5 6

	//4 5 6
	//1 2 3

	Matrix<int> a = { {1,2,3},{4,5,6} };
	Matrix<int> r = { {4,5,6},{1,2,3} };

	ASSERT_NO_THROW(a.SwapUD());
	ASSERT_TRUE(a.SwapUD() == r);

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



