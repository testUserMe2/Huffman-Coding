#ifndef _STRING_HEADER

#define _STRING_HEADER

#include <iostream>
#include <fstream>
#include <cassert>
#include "DynArray.h"
using namespace std;

class String
{
	DynArray<char > m_arr;
public:

	friend istream & operator>>(istream &in, String & obj);
	friend ostream & operator<<(ostream &out, const String & obj);

	String() : m_arr(){};
	String(char *newStr)  { setCharArray(newStr); }

	String(const String &right) { m_arr.copy(right.getCharArr()); }

	String & operator = (const String &right)
	{
		if (this != &right)
		{
			m_arr.cleanArray();
			m_arr.copy(right.getCharArr());
		}
		return *this;
	}

	~String() { }

	int getSize() { return m_arr.getSize(); }
	int getCapacity() { return m_arr.getCapacity(); }
	char * getCharArr() { return m_arr.getArr(); }

	const int getSize() const { return m_arr.getSize(); }
	const int getCapacity() const { return m_arr.getCapacity(); }

	const char * getCharArr() const { return m_arr.getArr(); }

	void setCapacity(int newCap) { m_arr.setCapacity(newCap); }
	void setSize(int newSize) { m_arr.setSize(newSize); }
	void setCharArray(char *newStr)
	{
		char c;
		int i = 0;
		while ((c = newStr[i]) != '\0'){
			m_arr.insert(c);
			++i;
		}
		c = '\0';
		m_arr.insert('\0');
	}

	void addOneChar(char newChar) { m_arr.insert(newChar); }

	char & operator [] (const int index);
	const char & operator [] (const int index) const; // for const objects

	friend bool operator==(const String & right, const String & left)
	{
		if (!(strcmp(right.getCharArr(), left.getCharArr())))
			return true;
		return false;
	}
	friend bool operator!=(const String & right, const String & left)
	{
		return !(right == left);
	}

	void clearString()	{	m_arr.cleanArray();	}

private:
	void resize(int newCapacity) {
		m_arr.resize(newCapacity);
		m_arr.insert('\0');
	}
	void String::copy(const String &right) { m_arr.copy(right.m_arr); }
};


#endif // !_STRING_HEADER