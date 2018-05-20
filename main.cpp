#include <iostream>

#include <fstream>
#include "String.h"
#include "DynArray.h"
#include "StaticArray.h"
#include "Word.h"
#include "HuffmanBinaryThree.h"
#include "Heap.h"
#include "FileParse.h"


using namespace std;


/**
*  
* Solution to Project
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Martin Vrachev
* @idnumber 45197
* @task 0 - project
* @compiler VC - Visual Studio
*
*/


/********************************************//**
 *  Encode functions declarations :
***********************************************/

bool isInsideContainer(bool *isItInFileArr,
	const unsigned short & wordForEncode);

void setContainerWithWords(StaticArray<short, 2048> & readArr, int * wordAmountInFile,
	DynArray<HuffmanBinaryTree> & container, int & wordsInFile);

void findWordsInFile(const char * filePath, int countEqualWords[], DynArray<HuffmanBinaryTree> & container, int & wordsInFile);

void setWordsVariations(DynArray<HuffmanBinaryTree> & allWords, int countEqualWords[], int wordsInFile);

void copyWordsToHeap(DynArray<HuffmanBinaryTree> & allWords, Heap<HuffmanBinaryTree> & allWordsInMinHeap);

/// I make a copy of the all words heap because I nedd it later
HuffmanBinaryTree createHufmanTreeForEncode(Heap<HuffmanBinaryTree> allWords);

void writeEncoding(ofstream & resultFile, const DynArray<bool> & code, char & wordWithCodes,
	short & bitShift, StaticArray<char, 2048> & codeResuts);

void encodeFile(const char * inputFilePath, const char * resultFilePath, const DynArray<Word> & codes);
void writeMetaData(ofstream & fileResult, Heap<HuffmanBinaryTree> & allWordsInFle);



/********************************************//**
*  Decode functions declarations:
************************************************/


void readForDecode(ifstream & codedFile, Heap<HuffmanBinaryTree> & onlyWords);

DynArray<bool> getCode(char word);

void decodeToFirstFile(ofstream & firstFile, ifstream & decodedFIle, HuffmanBinaryTree & tree, int & bitShift);

void decodeWork(ifstream & decodedFile, int amountOfWordsInFile);


// ************************************************************** //


void testMergeHuffmanThrees(){

	Word leftWord(1, 0.3f);
	HuffmanBinaryTree leftTree(leftWord);
	Word rightWord(2, 0.8f);
	HuffmanBinaryTree rightTree;

	HuffmanBinaryTree result;
	result = HuffmanBinaryTree::mergeHufmanTrees(leftTree, rightTree);
	std::cout << result << endl;
}


void testOperatorEqualInHuffman(){
	Word leftWord(1, 0.3f);
	HuffmanBinaryTree leftTree(leftWord);
	HuffmanBinaryTree rightTree;
	rightTree = leftTree;
	std::cout << rightTree << endl;
}


void simpleTest1(String & inputFileNme, String & outPutFileName){

	inputFileNme = "Test1.txt";
	outPutFileName = "Result.txt";

	StaticArray<short, 2048> test;
	short arr[9] = { 1, 2, 2, 4, 1, 20, 30, 3, 2 };
	int arrSize = 9;

	for (int i = 0; i < arrSize; ++i)
	{
		test.insert(arr[i]);
		cout << arr[i] << "	";
	}

	FileParse<short, 2048> writeTest(inputFileNme.getCharArr(), "writeFile");
	writeTest.parseWriteFile(test);
	writeTest.closeFile();
}


void printCodes(const DynArray<Word> & codes){

	int size = codes.getSize();

	cout << "\nNumber of words with code: " << size << endl;

	for (int i = 0; i < size; ++i)
	{
		cout << "Code for " << codes[i].getWordForEncode() << " is: ";
		cout << codes[i].getCode() << endl;
	}
}


void printAllWordsInThree(Heap<HuffmanBinaryTree> & allWordsInMinHeap){

	int sizeAllWords = allWordsInMinHeap.getSize();
	for (int i = 0; i < sizeAllWords; ++i)
	{
		if ( allWordsInMinHeap[i].isWordInTree(allWordsInMinHeap[i].getRootData().getCode(), allWordsInMinHeap[i].getRootData()) == false)
		{
			cout << "\n---------------------------------------------------------\n";
			cout << "WORD: " << allWordsInMinHeap[i].getRootData() << " is NOT in the tree!!!\n";
		}
	}
}


void allWordsInFile(const String inputFileName, int countEqualWords[], int & amountOfWordsInFile, DynArray<HuffmanBinaryTree> & allWords){

	findWordsInFile(inputFileName.getCharArr(), countEqualWords, allWords, amountOfWordsInFile);

	int getAmountAllWords = allWords.getSize();

	int index = 0;
	cout << allWords << endl;

	cout << "\nAll words in the file are: " << getAmountAllWords << endl;
}

int main(){

	try
	{

		String inputFileNme = "Test1.txt";

	    String outPutFileName = "Result.txt";

		simpleTest1(inputFileNme, outPutFileName);

		const String inputFile = inputFileNme;
		

		ifstream readFile(inputFile.getCharArr(), ios::in | ios::binary);

		/********************************************//**
		 *  At first I must save the words in an array because I can't put them into a heap
		*  because they wont have any variation
		************************************************/

		DynArray<HuffmanBinaryTree> allWords;

		cout << "\n-------------------------ALL_WORDS_AMOUNT_IN_FILE--------------------------------\n";

		int amountOfWordsInFile = 0;

		// In the parameter countEqualWords I would count 
		// every single char how man times is in the file
		const int MAX_SHORT_CAP = 65536;
		int countEqualWords[MAX_SHORT_CAP] = { 0, };

		allWordsInFile(inputFileNme, countEqualWords, amountOfWordsInFile, allWords);

		cout << "\n--------------------------All_WORDS_VARIATIONS------------------------------\n";


		setWordsVariations(allWords, countEqualWords, amountOfWordsInFile);

		// Here I use this heap as min heap
		Heap<HuffmanBinaryTree> allWordsInMinHeap;
		copyWordsToHeap(allWords, allWordsInMinHeap);

		cout << "\n-------------------------HUFMAN_TREE--------------------------------\n";

		cout << "first heap: ";
		cout << allWordsInMinHeap << endl;

		/// I will need this array when I save in the file
		HuffmanBinaryTree result;
		result = createHufmanTreeForEncode(allWordsInMinHeap);

		cout << "\n-----------------------CODES----------------------------------\n";

		DynArray<Word> codes;
	
		result.setAllCodes(codes);

		printCodes(codes);

		cout << "\n----------------------------ARE_ALL_WORDS_IN_TREE?-----------------------------\n";

		int sizeAllWords = allWordsInMinHeap.getSize();
		for (int i = 0; i < sizeAllWords; ++i)
		{
			if (allWordsInMinHeap[i].isWordInTree(allWordsInMinHeap[i].getRootData().getCode(), allWordsInMinHeap[i].getRootData()) == false)
			{
				cout << "\n---------------------------------------------------------\n";
				cout << "WORD: " << allWordsInMinHeap[i].getRootData() << " is NOT in the tree!!!\n";
			}
		}
		cout << "\n---------------------------------------------------------\n";

		system("PAUSE");
		encodeFile(inputFileNme.getCharArr(), outPutFileName.getCharArr(), codes);

		ifstream decodedFile(outPutFileName.getCharArr(), ios::in | ios::binary);


		cout << "\n---------------------------------------------------------\n";
		cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!Decoding!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

		/// decodeWork(decodedFile, amountOfWordsInFile);


	}
	catch (const char * problem)
	{
		cout << problem;
	}
	catch (const bad_alloc & problem)
	{
		cout << problem.what() << endl;
	}

	//testOperatorEqualInHuffman();
	//testMergeHuffmanThrees();

	
	return 0;
}