
#include <iostream>
#include <fstream>
#include "Word.h"
#include "DynArray.h"
using namespace std;


bool operator==(const Word & left, const Word & right)
{
	if (left.getWordInFileVariation() == right.getWordInFileVariation())
		return true;
	return false;
}


bool operator!=(const Word & left, const Word & right)
{
	return !(left.getWordInFileVariation() == right.getWordInFileVariation());
}


bool operator>(const Word & left, const Word & right)
{
	if (left.getWordInFileVariation() > right.getWordInFileVariation())
		return true;
	return false;
}



bool operator<(const Word & left, const Word & right)
{
	if (left.getWordInFileVariation() < right.getWordInFileVariation())
		return true;
	return false;
}