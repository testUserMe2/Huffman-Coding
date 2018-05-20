#ifndef _STATIC_ARRAY_HEADER

#define _STATIC_ARRAY_HEADER

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;



template<typename TYPE, const int MAX_CAPACITY>
class StaticArray
{
	TYPE *m_arr;
	int m_size;
	int m_capacity;
public:

	friend ostream & operator<<(ostream &out, const StaticArray & obj)
	{
		int size = obj.m_size;
		for (int i = 0; i < size; ++i)
		{
			out << obj.m_arr[i] << " ";
		}
		return out;
	}

	StaticArray() : m_arr(nullptr), m_size(0), m_capacity(0){}

	StaticArray(const StaticArray & right) { copy(right); }
	StaticArray & operator=(const StaticArray & right)
	{
		if (this != &right)
		{
			cleanArray();
			copy(right);
		}
		return *this;
	}

	~StaticArray(){ delete[] m_arr; }


	void copy(const StaticArray & right);

	void cleanArray()
	{
		delete[] m_arr;
		m_arr = NULL;
		m_size = 0;
		m_capacity = 0;
	}

	const int getSize() const { return m_size; }
	int getSize()  { return m_size; }

	int getCapacity() { return m_capacity; }
	const TYPE * getArr() const	{ return m_arr; }
	TYPE * getArr() { return m_arr; }

	void setSize(const int newSize) { m_size = newSize; }

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

	bool insert(const TYPE & newElement);
	void remove();
	bool resize(int newCapacity);



};

template <typename TYPE, const int MAX_CAPACITY>
inline void StaticArray<TYPE, MAX_CAPACITY>::copy(const StaticArray & right)
{
	m_arr = new TYPE[right.m_capacity];
	m_capacity = right.m_capacity;
	m_size = right.m_size;
	for (int i = 0; i < m_size; ++i)
		m_arr[i] = right.m_arr[i];
}


/// Inserts element in the end of the array
template <typename TYPE, const int MAX_CAPACITY>
inline bool StaticArray<TYPE, MAX_CAPACITY>::insert(const TYPE & newElement)
{
	if (m_capacity == 0)
		resize(5);
	if (m_capacity == m_size)
	{
		if (resize(m_capacity * 2) == false)
			return false;
	}
	m_arr[m_size] = newElement;
	++m_size;
	return true;
}


template <typename TYPE, const int MAX_CAPACITY>
inline void StaticArray<TYPE, MAX_CAPACITY>::remove()
{
	if (m_size == 0 || m_capacity == 0)
		return;
	if (m_capacity / 3 >= m_size)
		resize(m_capacity / 2);
	--m_size;
}


template <typename TYPE, const int MAX_CAPACITY>
inline bool StaticArray<TYPE, MAX_CAPACITY>::resize(int newCapacity)
{
	if (newCapacity > MAX_CAPACITY)
		return false;
	TYPE * temp = new TYPE[newCapacity];

	for (int i = 0; i < m_size; ++i)
		temp[i] = m_arr[i];

	delete[]m_arr;

	m_arr = temp;
	m_capacity = newCapacity;
	return true;
}



#endif // !_STATIC_ARRAY_HEADER
