#pragma once
#include <functional>
#include <initializer_list>


namespace Utils
{
	template<typename T>
	class Matrix
	{
	private:
		T* _data;
		size_t _size1, _size2;

		void InitData()
		{
			_data = (Size() > 0) ? new T[_size1 * _size2] : nullptr;
		}

	public:

			
		Matrix(size_t size1 = 0, size_t size2 = 0)
		{
			this->_size1 = size1;
			this->_size2 = size2;

			InitData();
		}

		Matrix(std::initializer_list<std::initializer_list<T>> list)
		{
			if (list.size() == 0)
			{
				_size1 = _size2 = 0;
				return;
			}

			_size1 = list.size();
			_size2 = 0;
			for (auto it = list.begin(); it!=list.end(); it++)
			{
				if (_size2 < it->size())
					_size2 = it->size();
			}

			InitData();

			if (Size() > 0)
			{
				int i1 = 0;
				for (auto it = list.begin(); it != list.end(); it++)
				{
					int i2 = 0;
					for (auto it2 = it->begin(); it2 != it->end(); it2++)
					{
						this->operator[](i1)[i2] = *it2;
						i2++;
					}

					i1++;
				}
			}
		}

		Matrix(const Matrix& other):Matrix(other._size1, other._size2)
		{
			if (Size() > 0)
				std::copy(other._data, other._data + other.Size(), _data);
		}

		~Matrix()
		{
			if (_data != nullptr)
			{
				delete[] _data;
			}
		}

		void FillBy(const Matrix<T>& from, std::function<void(size_t, size_t, size_t&, size_t&)> xyFunc)
		{
			for (size_t i1 = 0; i1 < from._size1; i1++)
			{
				for (size_t i2 = 0; i2 < from._size2; i2++)
				{
					size_t o1, o2;
					xyFunc(i1, i2, o1, o2);
					this->operator[](o1)[o2] = from[i1][i2];
				}
			}
		}

		Matrix<T> RotateR()
		{
			Matrix<T> result(_size2, _size1);

			//1 2 3
			//4 5 6

			//4 1
			//5 2
			//6 3
			int s1 = _size1;
			auto xyFunc = [s1](size_t i1, size_t i2, size_t& o1, size_t& o2) {
				o1 = i2;
				o2 = s1 - i1 - 1;
			};
				

			result.FillBy(*this, xyFunc);
			return result;
		}
		Matrix<T> RotateL()
		{
			Matrix<T> result(_size2, _size1);

			//1 2 3
			//4 5 6

			//3 6
			//2 5
			//1 4
			int s2 = _size2;
			auto xyFunc = [s2](size_t i1, size_t i2, size_t& o1, size_t& o2) {
				o1 = s2 - i2 - 1;
				o2 = i1;
			};

			result.FillBy(*this, xyFunc);
			return result;
		}
		Matrix<T> Rotate180()
		{
			Matrix<T> result(_size1, _size2);

			//1 2 3
			//4 5 6

			//6 5 4
			//3 2 1
			int s1 = _size1;
			int s2 = _size2;
			auto xyFunc = [s1, s2](size_t i1, size_t i2, size_t& o1, size_t& o2) {
				o1 = s1 - i1 - 1;
				o2 = s2 - i2 - 1;
			};


			result.FillBy(*this, xyFunc);
			return result;
		}

		Matrix<T> SwapLR()
		{
			Matrix<T> result(_size1, _size2);

			//1 2 3
			//4 5 6

			//3 2 1
			//6 5 4
			int s2 = _size2;
			auto xyFunc = [s2](size_t i1, size_t i2, size_t& o1, size_t& o2) {
				o1 = i1;
				o2 = s2 - i2 - 1;
			};


			result.FillBy(*this, xyFunc);
			return result;
		}
		Matrix<T> SwapUD()
		{
			Matrix<T> result(_size1, _size2);

			//1 2 3
			//4 5 6

			//4 5 6
			//1 2 3
			int s1 = _size1;
			auto xyFunc = [s1](size_t i1, size_t i2, size_t& o1, size_t& o2) {
				o1 = s1 - i1 - 1;
				o2 = i2;
			};


			result.FillBy(*this, xyFunc);
			return result;
		}


		Matrix& operator=(const Matrix& other)
		{
			if (this == &other)
				return *this;

			bool needToReInitData = Size() != other.Size();
			_size1 = other._size1;
			_size2 = other._size2;

			if (needToReInitData)
			{
				if(_data != nullptr)
					delete[] _data;

				InitData();
			}

				

			if (Size() > 0)
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

		T* operator[](int index) const
		{
			return _data + index * _size2;
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
	};
}



