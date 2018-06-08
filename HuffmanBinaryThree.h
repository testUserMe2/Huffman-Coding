#ifndef _HUFMAN_BINARY_TREE_HEADER

#define _HUFMAN_BINARY_TREE_HEADER


#include <iostream>

#include "Heap.h"
#include "Word.h"


class HuffmanBinaryTree
{
	struct Node
	{
		Word m_data;
		Node *m_leftChild, *m_rightChild;
		Node() : m_leftChild(nullptr), m_rightChild(nullptr){}
		Node(const Word & newData, Node * leftChild = nullptr, Node * rightChild = nullptr) :
			m_data(newData), m_leftChild(leftChild), m_rightChild(rightChild){}
		Word & getData() { return m_data; }
	};

	Node * root;
public:

	friend ostream & operator<<(ostream &out, const HuffmanBinaryTree & obj)
	{
		obj.print(out, obj.root);
		return out;
	}

	/// The mergeHufmanTrees is static function im HuffmanBinaryTree because none of the trees
	/// left or right has more priority than the the other but still I need to access
	/// the node Structure so I can create a new Node.
	static HuffmanBinaryTree mergeHufmanTrees(HuffmanBinaryTree & leftTree,
		HuffmanBinaryTree  & rightTree);


	HuffmanBinaryTree() : root(nullptr) {}

	HuffmanBinaryTree(const Word & newRootData) { root = new Node(newRootData); }

	HuffmanBinaryTree(const HuffmanBinaryTree & right) { root = copy(right.root); }

	HuffmanBinaryTree & operator=(const HuffmanBinaryTree & right)
	{
		if (this != &right)
		{
			clear(root);
			root = copy(right.root);
		}
		return *this;
	}

	~HuffmanBinaryTree(){ clear(root); }

	void clearTree() { clear(root); }

	Node * copy(Node * current)
	{
		if (current == nullptr)
			return current;
		return new Node(current->m_data, copy(current->m_leftChild), copy(current->m_rightChild));
	}

	const Word & getRootData() const { return root->m_data; }
	Word & getRootData() { return root->m_data; }

	void setAllCodes(DynArray<Word> & codeForWords)
	{
		DynArray<bool> code;
		setCodes(root, code, codeForWords);
	}
	

	bool isWordInTree(DynArray<bool> & path, Word & searchData);

	bool findALeaf(DynArray<bool> & path, Word & nowWord);

private:

	void print(ostream &out, const Node * current) const;

	void clear(Node *current)
	{
		if (current != nullptr)
		{
			clear(current->m_leftChild);
			clear(current->m_rightChild);
			delete current;
		}
	}

	void setCodes(Node *& current, DynArray<bool>  code, DynArray<Word> & codeForWords)
	{

		if (current != nullptr)
		{
			code.insert(0);
			setCodes(current->m_leftChild, code, codeForWords);
			code.remove();

			code.insert(1);
			setCodes(current->m_rightChild, code, codeForWords);
			code.remove();

			if (current->m_leftChild == nullptr && current->m_rightChild == nullptr)
			{
				Word newWord(current->getData());
				if (current == root)
					code.insert(0);
				code.resize(code.getSize());
				newWord.setHufmanCode(code);
				codeForWords.insert(newWord);
			}
		}
	}

};


bool operator==(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right);
bool operator!=(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right);
bool operator>(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right);
bool operator<(const HuffmanBinaryTree & left, const HuffmanBinaryTree & right);


#endif /// !_HUFMAN_BINARY_TREE_HEADER
