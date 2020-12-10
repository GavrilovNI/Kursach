#pragma once

namespace NeuralNet
{
	namespace Utils
	{
		template<typename T>
		class Matrix
		{
		private:
			T* _data;
			size_t _size1, _size2;

		public:

			template<typename Y>
			class InsideIndex
			{
			private:
				Y* _data;

			public:
				InsideIndex(Y* data)
				{
					this->_data = data;
				}

				Y& operator[](int index) const
				{
					return _data[index];
				}

			};

			
			Matrix(size_t size1 = 0, size_t size2 = 0)
			{
				this->_size1 = size1;
				this->_size2 = size2;

				if (_size1 != 0 && _size2 != 0)
				{
					_data = new T[_size1 * _size2];
				}
				else
				{
					this->_data = nullptr;
				}
			}

			Matrix(const Matrix& other):Matrix(other._size1, other._size2)
			{
				std::copy(other._data, other._data + other.Size(), _data);
			}

			~Matrix()
			{
				if (_size1 != 0 && _size2 != 0)
				{
					delete[] _data;
				}
			}

			Matrix& operator=(const Matrix& other)
			{
				if (this == &other)
					return *this;

				if (Size() != other.Size())
				{
					delete[] _data;

					_size1 = other._size1;
					_size2 = other._size2;

					_data = new T[_size1 * _size2];
				}

				std::copy(other._data, other._data + other.Size(), _data);

				return *this;
			}

			bool operator==(const Matrix& other)
			{
				if (this == &other)
					return true;

				if (_size1 != other._size1 || _size2 != other._size2)
					return false;

				for (size_t i = 0; i < Size(); i++)
				{
					if (_data[i] != other._data[i])
						return false;
				}
				return true;
			}

			bool operator!=(const Matrix& other)
			{
				return !operator==(other);
			}

			size_t GetSize(uint32_t dimension) const
			{
				if (dimension > 1)
					throw std::invalid_argument("dimension may be only 0 or 1");

				if (dimension == 0)
					return _size1;
				else
					return _size2;
			}

			int Size() const
			{
				return _size1 * _size2;
			}

			T * operator[](int index) const
			{
				return _data + index * _size2;
			}
		};
	}
}



