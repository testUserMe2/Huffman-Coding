#ifndef _FILE_PARSÅ_HEADER

#define _FILE_PARSÅ_HEADER

#include <iostream>
#include <fstream>
#include "StaticArray.h"

using namespace std;

template <typename ElementType, const int BUFF_SIZE>
class FileParse
{
	//DynArray<char> m_filePath;
	fstream m_file;
	bool isReadFile;

public:

	FileParse(const char * filePath, const char * fileType)
		//m_filePath(filePath)
	{
		if (strcmp(fileType, "readFile") == 0)
		{
			m_file.open(filePath, ios::in | ios::binary);
			if (!m_file.good())
				throw "Problem! The read file you want to open was not opened!\n";
			isReadFile = true;
		}
		else if (strcmp(fileType, "writeFile") == 0)
		{
			m_file.open(filePath, ios::out | ios::binary);
			if (!m_file.good())
				throw "Problem! The write file you want to open was not opened!\n";
			isReadFile = false;
		}
		else
			throw "\nYou have not created object of type File Parse!\n Please use readFile for ifstream and writeFile for ofstream!\n";

	}

	void closeFile(){ m_file.close(); }

	~FileParse(){ m_file.close(); }

	int getFileBytesAmount()
	{
		int bytesAmount = 0;
		if (isReadFile == true)
		{
			m_file.seekg(0, m_file.cur);
			int current = (int)m_file.tellg();
			m_file.seekg(0, m_file.end);
			int end = (int)m_file.tellg();
			m_file.seekg(current, m_file.beg);
			bytesAmount = end - current;
		}
		else
		{
			m_file.seekp(0, m_file.cur);
			int current = (int)m_file.tellp();
			m_file.seekp(0, m_file.end);
			int end = (int)m_file.tellp();
			m_file.seekp(current, m_file.beg);
			bytesAmount = end - current;
		}
		return bytesAmount;
	}

	void parseReadFile(StaticArray<ElementType, BUFF_SIZE> & result);
	void parseWriteFile(StaticArray<ElementType, BUFF_SIZE> & input);

};



template<typename ElementType, const int BUFF_SIZE>
void FileParse<ElementType, BUFF_SIZE>::parseReadFile(StaticArray<ElementType, BUFF_SIZE> & result)
{
	if (isReadFile == false)
		throw "Problem! You try to use parseReadFile function when you use ofstream!\n";
	int numBytes = getFileBytesAmount();

	int remainingElements = numBytes / sizeof(ElementType);

	if (remainingElements > BUFF_SIZE)
	{
		m_file.read((char*)result.getArr(), sizeof(ElementType)*BUFF_SIZE);
		result.setSize(BUFF_SIZE);
	}
	else
	{
		m_file.read((char*)result.getArr(), sizeof(ElementType)*remainingElements);
		result.setSize(remainingElements);
	}
}



template<typename ElementType, const int BUFF_SIZE>
void FileParse<ElementType, BUFF_SIZE>::parseWriteFile(StaticArray<ElementType, BUFF_SIZE> & input)
{
	if (isReadFile == true)
		throw "Problem! You try to use parseWriteFile function when you use ifstream!\n";
	if (input.getSize() == 0)
		return;

	m_file.write((char*)input.getArr(), sizeof(ElementType)*input.getSize());
}

#endif // !_FILE_PARSÅ_HEADER