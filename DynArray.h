#ifndef _DYN_ARRAY_HEADER

#define _DYN_ARRAY_HEADER 
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;
template <typename TYPE>
class DynArray
{
	TYPE *m_arr;
	int m_size;
	int m_capacity;
public:
	friend ostream & operator<<(ostream &out, const DynArray & obj)
	{
		int size = obj.m_size;
		for (int i = 0; i < size; ++i)
		{
			out << obj.m_arr[i] << " ";
		}
		return out;
	}

	DynArray() : m_arr(nullptr), m_size(0), m_capacity(0){}

	DynArray(TYPE * newArr, int size)
	{
		m_arr = new TYPE[size * 2];
		m_size = size;
		m_capacity = size * 2;
		for (int i = 0; i < m_size; ++i)
		{
			m_arr[i] = newArr[i];
		}
	}

	DynArray(const char * newArr)
	{
		m_size = strlen(newArr);
		m_capacity = m_size + 1;
		m_arr = new TYPE[m_capacity];
		for (int i = 0; i < m_size; ++i)
		{
			m_arr[i] = newArr[i];
		}
		m_arr[m_size] = '\0';
	}

	DynArray(const DynArray & right) { copy(right); }

	DynArray & operator= (const DynArray & right)
	{
		if (this != &right)
		{
			cleanArray();
			copy(right);
		}
		return *this;
	}

	~DynArray() { delete[] m_arr; }

	void copy(const DynArray & right);

	void cleanArray()
	{
		delete[] m_arr;
		m_arr = NULL;
		m_size = 0;
		m_capacity = 0;
	}

	const int getSize() const { return m_size; }
	int getSize()  { return m_size; }
	
	const int getCapacity() const { return m_capacity; }
	int getCapacity() { return m_capacity; }

	void setSize(const int newSize) { m_size = newSize;  }
	void setCapacity(const int newCap) { m_capacity = newCap;}

	const TYPE * getArr() const	{ return m_arr; }
	TYPE * getArr() { return m_arr; }

	void resize(int newCapacity);

	void insert(const TYPE & newElement);		/// Add element at the end
	bool remove();
	void removeAtIndex(int index);

	TYPE & operator[](int index)
	{
		assert(index >= 0 && index < m_size);

		return m_arr[index];
	}

	const TYPE  & operator[] (int index) const		/// for const objects, can only be used for access
	{
		assert(index >= 0 && index < m_size);

		return m_arr[index];
	}

	bool operator==(const DynArray & right);
	bool operator!=(const DynArray & right);

	void mergeSort();
private:
	void mergeStep(TYPE * arr, int size, TYPE * buffer);
	void merge(TYPE * arr1, int size1, TYPE * arr2, int size2, TYPE * result);

};


template <typename TYPE>
inline bool DynArray<TYPE>::operator==(const DynArray & right)
{
	if (m_size != right.m_size)
		return false;
	for (int i = 0; i < m_size; ++i)
	{
		if (m_arr[i] != right.m_arr[i])
			return false;
	}
	return true;

}

template <typename TYPE>
inline bool DynArray<TYPE>::operator!=(const DynArray & right)
{
	return !(*this == right);
}



template <typename TYPE>
inline void DynArray<TYPE>::copy(const DynArray & right)
{
	m_arr = new TYPE[right.m_capacity];
	m_capacity = right.m_capacity;
	m_size = right.m_size;
	for (int i = 0; i < m_size; ++i)
		m_arr[i] = right.m_arr[i];
}


// For char *
template <>
inline void DynArray<char>::copy(const DynArray<char> & right)
{
	m_arr = new char[right.m_capacity];
	m_capacity = right.m_capacity;
	m_size = right.m_size;
	for (int i = 0; i < m_size; ++i)
		m_arr[i] = right.m_arr[i];
	m_arr[m_size] = '\0';
}


template <typename TYPE>
inline void DynArray<TYPE>::resize(int newCapacity)
{
	TYPE * temp = new TYPE[newCapacity];

	for (int i = 0; i < m_size; ++i)
		temp[i] = m_arr[i];

	delete[]m_arr;

	m_arr = temp;
	m_capacity = newCapacity;
}


// For char *
template <>
inline void DynArray<char>::resize(int newCapacity)
{
	char * temp = new char[newCapacity];

	for (int i = 0; i < m_size; ++i)
		temp[i] = m_arr[i];
	temp[m_size] = '\0';
	delete[]m_arr;

	m_arr = temp;
	m_capacity = newCapacity;
}



/// Inserts element in the end of the array
template <typename TYPE>
inline void DynArray<TYPE>::insert(const TYPE & newElement)
{
	if (m_capacity == 0)
		resize(5);
	if (m_capacity == m_size)
		resize(m_capacity * 2);

	m_arr[m_size] = newElement;
	++m_size;
}


template <typename TYPE>
inline bool DynArray<TYPE>::remove()
{
	if (m_size == 0 || m_capacity == 0)
		return false;
	if (m_capacity / 3 >= m_size)
		resize(m_capacity / 2);
	--m_size;
	return true;
}
template <typename TYPE>
void DynArray<TYPE>::removeAtIndex(int index)
{
	if (index >= m_size)
		return;
	for (int i = index; i < m_size - 1; ++i)
		m_arr[i] = m_arr[i + 1];
	--m_size;
}


template <typename TYPE>
void DynArray<TYPE>::mergeSort()
{
	if (m_arr == nullptr || m_size <= 1)
		return;
	TYPE * buff = new TYPE[m_size];

	mergeStep(m_arr, m_size, buff);

	delete[]buff;
}

template <typename TYPE>
void DynArray<TYPE>::mergeStep(TYPE * arr, int size, TYPE * buffer)
{
	if (size <= 1)
		return;

	int middle = size / 2;

	mergeStep(arr, middle, buffer);
	mergeStep(arr + middle, size - middle, buffer);

	merge(arr, middle, arr + middle, size - middle, buffer);

	for (int i = 0; i < size; ++i)
	{
		arr[i] = buffer[i];
	}
}


template <typename TYPE>
inline void DynArray<TYPE>::merge(TYPE * arr1, int size1, TYPE * arr2, int size2, TYPE * result)
{
	int index1 = 0;
	int index2 = 0;
	int indexResult = 0;
	while (index1 < size1 && index2 < size2)
	{
		if (arr1[index1] > arr2[index2])
		{
			result[indexResult] = arr2[index2];
			++index2;
			++indexResult;
		}
		else
		{
			result[indexResult] = arr1[index1];
			++index1;
			++indexResult;
		}
	}
	while (index1 < size1)
	{
		result[indexResult] = arr1[index1];
		++index1;
		++indexResult;
	}
	while (index2 < size2)
	{
		result[indexResult] = arr2[index2];
		++index2;
		++indexResult;
	}

}


#endif /// !_DYN_ARRAY_HEADER