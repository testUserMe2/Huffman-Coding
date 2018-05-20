#include <iostream>
#include <fstream>
#include "DynArray.h"
#include "StaticArray.h"
#include "Word.h"
#include "HuffmanBinaryThree.h"
#include "Heap.h"
using namespace std;

/// I make a copy of the all words heap because I nedd it later
HuffmanBinaryTree createHufmanTreeForEncode(Heap<HuffmanBinaryTree> allWords);

void readAllEncodedWords(ifstream & codedFile)
{

}

void readForDecode(ifstream & codedFile, Heap<HuffmanBinaryTree> & onlyWords)
{
	int numberAllWords = 0;
	codedFile.read((char *)&numberAllWords, sizeof(numberAllWords));
	int numAllWordsCopy = numberAllWords;
	cout << "elements in arr: " << numberAllWords << endl;
	StaticArray<short, 2048> allWordsShorts;
	while (true)
	{
		if (numAllWordsCopy > 2048)
		{
			//codeFile.read((char*)&)
		}
	}
	for (int i = 0; i < numberAllWords; ++i)
	{
		short wordForEncode = 0;
		codedFile.read((char*)&wordForEncode, sizeof(wordForEncode));
		float variation = 0;
		codedFile.read((char*)&variation, sizeof(variation));

		Word newWord(wordForEncode, variation);
		HuffmanBinaryTree newTree(newWord);
		onlyWords.insert(newTree);
	}
}



DynArray<bool> getCode(char word)
{
	DynArray<bool> result;
	int bitSwift = 0;
	char zero = NULL;
	for (int i = 7; i >= 0; --i)
	{
		char tempWord = word & (1 << i);
		if (tempWord == 0)
			result.insert(0);
		else
			result.insert(1);
	}
	return result;
}



void decodeToFirstFile(ofstream & firstFile, ifstream & decodedFIle, HuffmanBinaryTree & tree, int amounOfWordsInFile)
{
	char word;
	Word newWord;
	DynArray<char> allWords;
	while (decodedFIle.read((char *)&word, sizeof(word)))
	{
		allWords.insert(word);
	}
	while (amounOfWordsInFile != 0)
	{
		if (tree.findALeaf(getCode(word), newWord) == true)
		{
			firstFile.write((char*)&newWord.getWordForEncode(), sizeof(short));
			--amounOfWordsInFile;
		}
	}
}


/// All the work the decoding will do
void decodeWork(ifstream & decodedFile, int amounOfWordsInFile)
{

	/// ifstream readMetaData("ResultTest.txt", ios::in | ios::binary);

	/// ifstream readMetaData("ResultForBigDaddy.txt", ios::in | ios::binary);

	Heap<HuffmanBinaryTree> readAllWords;

	readForDecode(decodedFile, readAllWords);
	cout << "Second heap: ";
	cout << readAllWords << endl;
	HuffmanBinaryTree decodeHufmanTree;
	decodeHufmanTree = createHufmanTreeForEncode(readAllWords);

	cout << "\n----------------------------ARE_ALL_WORDS_IN_TREE?-----------------------------\n";

	int sizeAllWords = readAllWords.getSize();
	for (int i = 0; i < sizeAllWords; ++i)
	{
		if (readAllWords[i].isWordInTree(readAllWords[i].getRootData().getCode(), readAllWords[i].getRootData()) == false)
		{
			cout << "\n---------------------------------------------------------\n";
			cout << "WORD: " << readAllWords[i].getRootData() << " is NOT in the tree!!!\n";
		}
	}
	cout << "\n---------------------------------------------------------\n";

	/// ofstream firstFile("FirstBIG_DADY_FILE.txt", ios::out | ios::binary);
	ofstream firstFile("FirstTESTfile.txt", ios::out | ios::binary);
	/// ofstream firstFile("FirstCHARfile.txt", ios::out | ios::binary);

	int bitShift = 0;
	decodeToFirstFile(firstFile, decodedFile, decodeHufmanTree, amounOfWordsInFile);

	decodedFile.close();

}