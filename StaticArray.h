#ifndef _STATIC_ARRAY_HEADER

#define _STATIC_ARRAY_HEADER

#include <iostream>
#include <fstream>

using namespace std;

template<typename TYPE, const int MAX_CAPACITY>
class StaticArray
{
	DynArray<TYPE> m_arr;
public:

	StaticArray() {	m_arr.resize(MAX_CAPACITY);	}

	StaticArray(const StaticArray & right) { m_arr.copy(right.m_arr); }
	StaticArray & operator=(const StaticArray & right)
	{
		if (this != &right)
		{
			m_arr = right.m_arr;
		}
		return *this;
	}

	~StaticArray(){}

	const int getSize() const { return m_arr.getSize(); }
	int getSize()  { return m_arr.getSize(); }

	int getCapacity() { return m_capacity; }
	const TYPE * getArr() const	{ return m_arr.getArr(); }
	TYPE * getArr() { return m_arr.getArr(); }

	void setSize(const int newSize) { m_arr.setSize(newSize); }

	bool insert(const TYPE & newElement);
	void remove() { m_arr.remove(); }
	void cleanArray() { m_arr.cleanArray(); }

	TYPE & operator[](int index) { return m_arr[index]; }

	const TYPE  & operator[] (int index) const	{ return m_arr[index]; }	/// for const objects, can only be used for access

};



/// Inserts element in the end of the array
template <typename TYPE, const int MAX_CAPACITY>
inline bool StaticArray<TYPE, MAX_CAPACITY>::insert(const TYPE & newElement)
{
	if (m_arr.getSize() >= MAX_CAPACITY){
		return false;
	}

	m_arr.insert(newElement);
	return true;
}


#endif // !_STATIC_ARRAY_HEADER
