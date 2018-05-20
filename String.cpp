#include <iostream>
#include "String.h"

using namespace std;

void String::resize(int newCapacity)
{
	char *temp = new char[newCapacity];
	for (int i = 0; i < m_size; ++i)
		temp[i] = str[i];
	delete[]str;
	str = new char[newCapacity];
	for (int i = 0; i < m_size; ++i)
		str[i] = temp[i];
	str[newCapacity - 1] = '\0';
	m_capacity = newCapacity;
	delete[]temp;
}

char & String::operator[](const int index)
{
	assert(index >= 0 && index < m_capacity);
	return str[index];
}


const char & String::operator[](const int index) const
{
	assert(index >= 0 && index < m_capacity);
	return str[index];
}

bool operator==(const String & right, const String & left)
{
	if (!(strcmp(right.getCharArr(), left.getCharArr())))
		return true;
	return false;
}
bool operator!=(const String & right, const String & left)
{
	return !(right == left);
}

ostream & operator<<(ostream &out, const String & obj)
{
	if (obj.getCapacity() != 0)
		cout << obj.str;
	return out;
}

void String::copy(const String &right)
{
	m_capacity = right.m_capacity;
	str = new char[m_capacity];
	m_size = right.m_size;
	for (int i = 0; i < m_size; ++i)
		str[i] = right.str[i];
	str[m_size] = '\0';
}
