#include <iostream>
#include <fstream>
#include "DynArray.h"
#include "StaticArray.h"
#include "Word.h"
#include "HuffmanBinaryThree.h"
#include "Heap.h"
#include "FileParse.h"
using namespace std;


bool isInsideContainer(bool *isItInFileArr,
	const unsigned short & wordForEncode)
{
	return isItInFileArr[wordForEncode] == true ? true : false;
}


// In the parameter countEqualWords I would count 
// every single char how man times is in the file

void setContainerWithWords(StaticArray<unsigned short, 2048> & readArr,
	int * countEqualWords, DynArray<HuffmanBinaryTree> & container, int & wordsInFile)
{
	Word newWord;
	int size = readArr.getSize();
	int readArrIndex = 0;

	const int MAX_SHORT_CAP = 65536;
	bool isItInFileArr[MAX_SHORT_CAP] = { 0, };
	while (readArrIndex < size)
	{
		int elemIndex = 0;
		if (isInsideContainer(isItInFileArr, readArr[readArrIndex]) == false)
		{
			newWord.setWordForEncode(readArr[readArrIndex]);
			container.insert(newWord);
			elemIndex = container.getSize() - 1;

			// That way I remember that I have seen this word
			isItInFileArr[readArr[readArrIndex]] = true;
		}
		
		// This increase the amount of times the word is in the file
		countEqualWords[readArr[readArrIndex]]++;

		++wordsInFile;
		++readArrIndex;
	}
}


// In the parameter countEqualWords I would count 
// every single char how man times is in the file

void findWordsInFile(const char * filePath, int countEqualWords[], DynArray<HuffmanBinaryTree> & container, int & wordsInFile)
{
	FileParse<unsigned short, 2048> readFile(filePath, "readFile");
	int RemainBytes = readFile.getFileBytesAmount();
	int RemainingShorts = RemainBytes / 2;
	StaticArray<unsigned short, 2048> readArr;

	while (RemainingShorts != 0)
	{
		readFile.parseReadFile(readArr);

		setContainerWithWords(readArr, countEqualWords, container, wordsInFile);
		RemainingShorts -= readArr.getSize();
		readArr.cleanArray();
		if (RemainingShorts == 0)
		{
			if (RemainBytes % 2 == 1)
			{
				StaticArray<unsigned short, 2048> finalShort;
				readFile.parseReadFile(finalShort);
				setContainerWithWords(finalShort, countEqualWords, container, wordsInFile);
			}
			break;
		}
	}
}



void setWordsVariations(DynArray<HuffmanBinaryTree> & allWords, int countEqualWords[], int wordsInFile)
{
	int size = allWords.getSize();
	float currVariation = 0;
	for (int i = 0; i < size; ++i)
	{
		unsigned short currWord = allWords[i].getRootData().getWordForEncode();
		currVariation = (float)countEqualWords[currWord] / wordsInFile;
		allWords[i].getRootData().setVariation(currVariation);
	}
}

void copyWordsToHeap(DynArray<HuffmanBinaryTree> & allWords, Heap<HuffmanBinaryTree> & allWordsInMinHeap)
{
	int size = allWords.getSize();
	for (int i = 0; i < size; ++i)
		allWordsInMinHeap.insert(allWords[i]);
}


/// I make a copy of the all words heap because I nedd it later
HuffmanBinaryTree createHufmanTreeForEncode(Heap<HuffmanBinaryTree> allWords)
{

	int numbersTreesToMerge = allWords.getSize();
	if (numbersTreesToMerge == 1)
		return allWords[0];
	HuffmanBinaryTree newTree;
	for (int i = 0; i < numbersTreesToMerge - 1; ++i)
	{
		newTree =
			HuffmanBinaryTree::mergeHufmanTrees(allWords.extractElemHighestPriority(), allWords.extractElemHighestPriority());
		allWords.insert(newTree);
	}
	int me = 0;
	return newTree;
}



void writeEncoding(FileParse<char, 2048> & resultFile, StaticArray<char, 2048> & codeResults,
	const DynArray<bool> & code, char & wordWithCodes, short & bitShift)
{
	int sizeCode = code.getSize();
	for (int i = 0; i < sizeCode; ++i)
	{
		if (bitShift == 8)
		{
			bitShift = 0;
			if (codeResults.insert(wordWithCodes) == false)
			{
				resultFile.parseWriteFile(codeResults);
				codeResults.cleanArray();
				codeResults.insert(wordWithCodes);
			}
			wordWithCodes = NULL;
		}
		if (code[i] == 1)
			wordWithCodes = wordWithCodes * 2 + 1;
		if (code[i] == 0)
			wordWithCodes = wordWithCodes << 1;
		++bitShift;
	}
}



void encodeFile(const char * inputFilePath, const char * resultFilePath, const DynArray<Word> & codes)
{
	FileParse<unsigned short, 2048> readFile(inputFilePath, "readFile");
	int bytesInFile = readFile.getFileBytesAmount();
	int shortsInFile = bytesInFile / 2;
	int readedShorts = 0;
	int amountCodes = codes.getSize();

	char newCode = NULL;
	short bitShift = 0;
	StaticArray<unsigned short, 2048> words;
	FileParse<char, 2048> resultFile(resultFilePath, "writeFile");
	StaticArray<char, 2048> codeResults;
	while (readedShorts < shortsInFile)
	{
		readFile.parseReadFile(words);
		readedShorts += words.getSize();
		int numReadedWords = words.getSize();
		for (int j = 0; j < numReadedWords; ++j)
		{
			for (int i = 0; i < amountCodes; ++i)
			{
				if (words[j] == codes[i].getWordForEncode())
				{
					writeEncoding(resultFile, codeResults, codes[i].getCode(), newCode, bitShift);
					break;
				}
			}
		}
		words.cleanArray();
	}
	readFile.closeFile();


	StaticArray<char, 2048> word;
	FileParse<char, 2048> readOneWord(inputFilePath, "readFile");
	if (bytesInFile % 2 == 1)
	{
		readOneWord.parseReadFile(word);
		//cout << word << endl;
		for (int i = 0; i < amountCodes; ++i)
		{
			if (word[0] == codes[i].getWordForEncode())
			{
				writeEncoding(readOneWord, codeResults, codes[i].getCode(), newCode, bitShift);
				break;
			}
		}
	}
	if (bitShift != 0)
	{
		newCode = newCode << (8 - bitShift);
		codeResults.insert(newCode);
	}
	resultFile.parseWriteFile(codeResults);
}

void writeAllWordsEncode(ofstream & fileResult, int numberAllWords, Heap<HuffmanBinaryTree> & allWordsInFle)
{
	StaticArray<short, 2048> allWordsForEncode;
	for (int i = 0; i < numberAllWords; ++i)
	{
		if (allWordsForEncode.insert(allWordsInFle[i].getRootData().getWordForEncode()) == false)
		{
			fileResult.write((char *)&allWordsForEncode, sizeof(short) * 2048);
			allWordsForEncode.cleanArray();
			allWordsForEncode.insert(allWordsInFle[i].getRootData().getWordForEncode());
		}
	}
	if (allWordsForEncode.getSize() != 0)
	{
		fileResult.write((char *)&allWordsForEncode, sizeof(short)* allWordsForEncode.getSize());
	}
}
