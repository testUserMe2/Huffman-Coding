#ifndef _STRING_HEADER

#define _STRING_HEADER

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

class String
{
	char *str;
	int m_size;
	int m_capacity;
public:

	friend istream & operator>>(istream &in, String & obj);
	friend ostream & operator<<(ostream &out, const String & obj);

	String() : str(nullptr), m_capacity(0), m_size(0){};
	String(char *newStr) { setCharArray(newStr); }

	String(const String &right){ copy(right); }

	String & operator = (const String &right)
	{
		if (this != &right)
		{
			delete[]str;
			copy(right);
		}
		return *this;
	}

	~String() { delete[] str; }

	int getSize() { return m_size; }
	int getCapacity() { return m_capacity; }
	char * getCharArr() { return str; }

	const int getSize() const { return m_size; }
	const int getCapacity() const { return m_capacity; }
	const char * getCharArr() const { return str; }

	void setCapacity(int newCap) { m_capacity = newCap; }
	void setSize(int newSize) { m_size = newSize; }
	void setCharArray(char *newStr)
	{
		m_size = strlen(newStr);
		m_capacity = m_size + 1;
		str = new char[m_capacity];
		for (int i = 0; i < m_size; ++i)
			str[i] = newStr[i];
		str[m_size] = '\0';
	}

	void addOneChar(char newChar)
	{
		if (m_capacity == 0)
			resize(16);
		if (m_size + 1 == m_capacity)
			resize(m_capacity * 2);
		str[m_size] = newChar;
		++m_size;

		str[m_size] = '\0';
	}

	char & operator [] (const int index);
	const char & operator [] (const int index) const; // for const objects

	friend bool operator==(const String & right, const String & left);
	friend bool operator!=(const String & right, const String & left);

	void clearString()
	{
		delete[]str;
		str = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

private:
	void resize(int newCapacity);
	void String::copy(const String &right);
};


#endif // !_STRING_HEADER
