#pragma once

#include <fstream>
#include <string>

/*
BUILD
GETSIZE
FINDMIN
SEARCH
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
	
	void BuildAvlTree(std::string line, std::ofstream& output);
	void InsertNode(std::string line);
	Node* InsertNode(Node* n, int value);
	Node* BalanceNode(Node* n);
	Node* RightRotation(Node* n);
	Node* LeftRotation(Node* n);
	void GetSize(std::string line, std::ofstream& output);
	
	int nodeBalanceFactor(Node* n);
private:
	Node* root;
	int elements;
	std::string ExtractFilename(std::string s);
	int ExtractNumber(std::string s);
};