#include <iostream>

#include "HuffmanBinaryThree.h"

using namespace std;


bool operator==(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right)
{
	if (left.getRootData() == right.getRootData())
		return true;
	return false;
}



bool operator!=(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right)
{
	return !(left.getRootData() == right.getRootData());
}



bool operator>(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right)
{
	if (left.getRootData() > right.getRootData())
		return true;
	return false;
}



bool operator<(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right)
{
	if (left.getRootData() < right.getRootData())
		return true;
	return false;
}


void HuffmanBinaryTree::print(ostream &out, const Node * current) const
{
	if (current != nullptr)
	{
		print(out, current->m_leftChild);
		cout << current->m_data.getWordForEncode() << ":" << current->m_data.getWordInFileVariation() << "  "; // Inorder traversal
		print(out, current->m_rightChild);
	}
}



bool HuffmanBinaryTree::isWordInTree(DynArray<bool> & path, Word & searchData)
{
	int size = path.getSize();
	Node * current = root;
	int index = 0;
	while (index < size)
	{
		if (current->m_leftChild != nullptr && path[index] == 0)
			current = current->m_leftChild;
		if (current->m_rightChild != nullptr && path[index] == 1)
			current = current->m_rightChild;
		++index;
	}
	if (searchData.getCode() == current->m_data.getCode() &&
		searchData.getWordForEncode() == current->m_data.getWordForEncode() &&
		searchData.getWordInFileVariation() == current->m_data.getWordInFileVariation())
		return true;

	return false;
}


bool HuffmanBinaryTree::findALeaf(DynArray<bool> & path, Word & nowWord)
{
	int size = path.getSize();
	Node * current = root;
	int index = 0;
	while (index < size)
	{
		if (current->m_leftChild == nullptr && current->m_rightChild == nullptr)
			break;
		if (current->m_leftChild != nullptr && path[index] == 0)
			current = current->m_leftChild;
		if (current->m_rightChild != nullptr && path[index] == 1)
			current = current->m_rightChild;
		++index;
	}

	if (current->m_leftChild == nullptr && current->m_rightChild == nullptr)
	{
		for (int i = 0; i < index; ++i)
			path.removeAtIndex(i);
		nowWord = current->m_data;
		return true;
	}
	return false;
}

HuffmanBinaryTree HuffmanBinaryTree::mergeHufmanTrees(HuffmanBinaryTree & leftTree, HuffmanBinaryTree & rightTree)
{
	if (leftTree.root == nullptr && rightTree.root == nullptr)
		return leftTree;

	HuffmanBinaryTree result;
	float rightTreeVariation = rightTree.root->m_data.getWordInFileVariation();
	float leftTreeVariation = leftTree.root->m_data.getWordInFileVariation();
	float fatherNodeVariation = rightTreeVariation + leftTreeVariation;
	if (leftTree.root != nullptr && rightTree.root == nullptr)
	{
		Word newWord(-1, leftTreeVariation);
		result.root = new HuffmanBinaryTree::Node(newWord);
		result.root->m_leftChild = leftTree.root;
	}
	else if (leftTree.root == nullptr && rightTree.root != nullptr)
	{
		Word newWord(-1, rightTreeVariation);
		result.root = new HuffmanBinaryTree::Node(newWord);
		result.root->m_rightChild = rightTree.root;
	}
	else
	{
		Word newWord(-1, fatherNodeVariation);
		result.root = new HuffmanBinaryTree::Node(newWord);
		result.root->m_rightChild = rightTree.root;
		result.root->m_leftChild = leftTree.root;
	}

	leftTree.root = nullptr;
	rightTree.root = nullptr;

	return result;
}
