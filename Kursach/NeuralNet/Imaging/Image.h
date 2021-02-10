#pragma once

#include <istream>
#include "../NeuralNet/Matrix.h";



namespace Imaging
{
	typedef char byte;

	struct Color
	{
		char r, g, b;

		Color(byte r, byte g, byte b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}

		friend std::istream& operator>>(std::istream& stream, const Color& dt);
		

	};

	std::istream& operator>>(std::istream& stream, Color& dt)
	{
		stream >> dt.r >> dt.g >> dt.b;
		return stream;
	}

	typedef Utils::Matrix<Color> Image;

	Image LoadImage(std::istream stream)
	{
		size_t size_x, size_y;

		stream >> size_x >> size_y;

		Image result(size_x, size_y);
		for (size_t y = 0; y < size_y; y++)
		{
			for (size_t x = 0; x < size_x; x++)
			{
				stream >> result[y][x];
			}
		}

		return result;
	}
}