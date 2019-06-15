#pragma once

#include <fstream>
#include <string>

/*
FINDMIN
INSERT
DELETE
*/

struct Node
{
	Node() = delete;
	Node(int v, Node* l, Node* r);
	int value;
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	int height();
};

class AVLTree
{
public:
	AVLTree();
	void Build(std::string filename);
	void Insert(int number);
	int GetSize() const;
	bool Search(int number) const;
	int GetMin() const;

private:
	Node* Insert(Node* n, int value);
	Node* BalanceNode(Node* n);
	Node* RightRotation(Node* n);
	Node* LeftRotation(Node* n);
	int nodeBalanceFactor(Node* n);

private:
	Node* root;
	int elements;
};