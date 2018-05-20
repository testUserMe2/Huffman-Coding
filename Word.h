#ifndef _WORD_HEADER

#define _WORD_HEADER

#include <iostream>
#include <fstream>
using namespace std;

#include "DynArray.h"


class Word
{
	// Unsigned because I use the word value as index in a bool array
	unsigned short m_wordForEncode;
	float m_wordInFileVariation; /// chance to see this word in the file
	DynArray<bool> m_hufmanCode;

public:

	friend ostream & operator<<(ostream &out, const Word & obj)
	{
		out << obj.m_wordForEncode;
		return out;
	}

	Word() : m_wordInFileVariation(0){};
	Word(const short & newWordForEncode, float newVariation = 0)
		:  m_wordInFileVariation(newVariation), m_wordForEncode(newWordForEncode){};


	unsigned short & getWordForEncode() { return m_wordForEncode; }
	const unsigned short & getWordForEncode() const { return m_wordForEncode; }

	float getWordInFileVariation() { return m_wordInFileVariation; }
	const float getWordInFileVariation() const { return m_wordInFileVariation; }

	DynArray<bool> & getCode() { return m_hufmanCode; }
	const DynArray<bool> & getCode() const { return m_hufmanCode; }

	void setWordForEncode(const short & newWord){ m_wordForEncode = newWord; }
	void setVariation(float newVariation){ m_wordInFileVariation = newVariation; }
	void setHufmanCode(const DynArray<bool> & newCode) { m_hufmanCode = newCode; }

};


bool operator==(const Word & left, const Word & right);
bool operator!=(const Word & left, const Word & right);
bool operator>(const Word & left, const Word & right);
bool operator<(const Word & left, const Word & right);

#endif /// !_WORD_HEADER
