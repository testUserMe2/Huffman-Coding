#ifndef _HEAP_HEADER

#define _HEAP_HEADER

#include <iostream>
#include <fstream>

#include "DynArray.h"

/**
*	I need to use that heap once as a minimum where the lowest elements has highest priority and
*	once as a maximum heap where the biggest elements are with highest priority.
*/
template<typename TYPE>
class Heap
{
	DynArray<TYPE> m_arr;

public:
	Heap(){};
	~Heap(){};

	friend ostream & operator<<(ostream &out, const Heap & obj)
	{
		out << obj.m_arr;
		return out;
	}

	const DynArray<TYPE> & getArr() { return m_arr; }
	int getSize() { return m_arr.getSize(); }
	const int getSize() const { return m_arr.getSize(); }

	void insert(const TYPE & newData, bool maxHeap = false);
	bool isEmpty() { return m_arr.getSize() == 0 ? true : false; }
	void remove(bool maxHeap = false);

	TYPE extractElemHighestPriority()
	{
		TYPE result = m_arr[0];
		remove();
		return result;
	}

	TYPE & operator[](int index) { return m_arr[index]; }

	/// for const objects, can only be used for access
	const TYPE  & operator[] (int index) const	{ return m_arr[index]; }

	/// I need maxHeap bool because I use my heap 
	/// as a minimum heap and as a maximum heap.
	void fixUp(int elemIndex, bool maxHeap);
	void fixDown(int elemIndex, bool maxHeap);
	void resize(int newCapacity){ m_arr.resize(newCapacity); }

};


template<typename TYPE>
void Heap<TYPE>::insert(const TYPE & newData, bool maxHeap)
{
	m_arr.insert(newData);
	fixUp(m_arr.getSize() - 1, maxHeap);
}



/// A function that fixes element priority upward after insert
/// so the heap property exists in the heap.
template<typename TYPE>
void Heap<TYPE>::fixUp(int elemIndex, bool maxHeap)
{
	while ((maxHeap == false && elemIndex >= 1 && m_arr[elemIndex] < m_arr[(elemIndex - 1) / 2]) ||
		(maxHeap == true && elemIndex >= 1 && m_arr[elemIndex] > m_arr[(elemIndex - 1) / 2]))
	{
		TYPE temp = m_arr[elemIndex];
		m_arr[elemIndex] = m_arr[(elemIndex - 1) / 2];
		m_arr[(elemIndex - 1) / 2] = temp;
		elemIndex = (elemIndex - 1) / 2;
	}
}



/// A function that fixes element priority downwards after remove 
/// so the heap property exists in the heap.
template<typename TYPE>
void Heap<TYPE>::fixDown(int fatherIndex, bool maxHeap)
{
	int size = m_arr.getSize();
	while (fatherIndex * 2 + 1 < size)
	{
		int mostPriorityChild = fatherIndex * 2 + 1;
		if (fatherIndex * 2 + 2 < size)
		{
			if (maxHeap == false)
			{
				mostPriorityChild = m_arr[fatherIndex * 2 + 1] < m_arr[fatherIndex * 2 + 2]
					? fatherIndex * 2 + 1 : fatherIndex * 2 + 2;
			}
			else
			{
				mostPriorityChild = m_arr[fatherIndex * 2 + 1] > m_arr[fatherIndex * 2 + 2]
					? fatherIndex * 2 + 1 : fatherIndex * 2 + 2;
			}
		}
		if ((maxHeap == false && m_arr[fatherIndex] < m_arr[mostPriorityChild]) ||
			(maxHeap == true && m_arr[fatherIndex] > m_arr[mostPriorityChild]))
			break;
		TYPE temp = m_arr[fatherIndex];
		m_arr[fatherIndex] = m_arr[mostPriorityChild];
		m_arr[mostPriorityChild] = temp;
		fatherIndex = mostPriorityChild;
	}
}


/// Removes the element with highest priority
template<typename TYPE>
void Heap<TYPE>::remove(bool maxHeap)
{
	if (isEmpty() == true)
		return;
	int size = m_arr.getSize();
	TYPE temp = m_arr[0];
	m_arr[0] = m_arr[size - 1];
	m_arr[size - 1] = temp;
	m_arr.remove();
	fixDown(0, maxHeap);
}

#endif /// !_HEAP_HEADER
