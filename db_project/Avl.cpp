#include "Avl.h"

Node::Node(int v, Node * l, Node * r)
{
	value = v;
	leftChild = l;
	rightChild = r;
}

int Node::height()
{
	int h = 0;
	if (this != nullptr) {
		int leftHeight = this->leftChild->height();
		int rightHeight = this->rightChild->height();
		int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
		h = maxHeight + 1;
	}
	return h;
}

AVLTree::AVLTree()
{
	root = nullptr;
	elements = 0;
}

void AVLTree::BuildAvlTree(std::string line, std::ofstream & output)
{
	auto filename = ExtractFilename(line);
	std::ifstream data(filename);

	std::string number;
	while (std::getline(data, number))
	{
		int x = std::stoi(number);
		root = InsertNode(root, x);
		elements += 1;
	}
}

void AVLTree::InsertNode(std::string line)
{
	int number = ExtractNumber(line);
	root = InsertNode(root, number);
	elements += 1;
}

Node* AVLTree::InsertNode(Node* n, int value)
{
	if (n == nullptr)
	{
		Node* n = new Node(value, nullptr, nullptr);
		return n;
	}
	else if (value <= n->value)
	{
		n->leftChild = InsertNode(n->leftChild, value);
	}
	else
	{
		n->rightChild = InsertNode(n->rightChild, value);
	}
	n = BalanceNode(n);
	return n;
}

Node* AVLTree::BalanceNode(Node* n)
{
	int nBalanceFactor = nodeBalanceFactor(n);

	if (nBalanceFactor >= -1 && nBalanceFactor <= 1)
	{
		return n;
	}

	int nVal = n->value;
	int leftGrandChildVal = n->leftChild ? n->leftChild->value : -1;
	int rightGrandChildVal = n->rightChild ? n->rightChild->value : -1;

	if (nBalanceFactor > 1)
	{
		if (n->leftChild->leftChild != nullptr) // LEFT LEFT
		{
			return RightRotation(n);
		}
		else if (n->leftChild->rightChild != nullptr) // LEFT RIGHT
		{
			n->leftChild = LeftRotation(n->leftChild);
			return RightRotation(n);
		}
	}
	else if (nBalanceFactor < -1)
	{
		if (n->rightChild->rightChild != nullptr) // RIGHT RIGHT
		{
			return RightRotation(n);
		}
		else if (n->rightChild->leftChild != nullptr) // RIGHT LEFT
		{
			n->rightChild = RightRotation(n->rightChild);
			return LeftRotation(n);
		}
	}
	/*
	//Left Left
	if (nBalanceFactor > 1 && nVal >= leftChildVal)
	{
		return RightRotation(n);
	}
	//Right Right
	if (nBalanceFactor < -1 && nVal <= rightChildVal)
	{
		return LeftRotation(n);
	}
	//Left Right
	if (nBalanceFactor > 1 && nVal <= leftChildVal)
	{
		n->leftChild = LeftRotation(n->leftChild);
		return RightRotation(n);
	}
	//Right Left  
	if (nBalanceFactor < -1 && nVal >= rightChildVal)
	{
		n->rightChild = RightRotation(n->rightChild);
		return LeftRotation(n);
	}*/

	return n;
}

Node * AVLTree::RightRotation(Node * n)
{
	Node* a = n->leftChild;
	n->leftChild = a->rightChild;
	a->rightChild = n;

	return a;
}

Node * AVLTree::LeftRotation(Node * n)
{
	Node* a = n->rightChild;
	n->rightChild = a->leftChild;
	a->leftChild = n;

	return a;
}

void AVLTree::GetSize(std::string line, std::ofstream & output)
{
	output << line << "\t\t" << elements << " elements\n";
}

int AVLTree::nodeBalanceFactor(Node * n)
{
	return (n->leftChild->height() - n->rightChild->height());
}

std::string AVLTree::ExtractFilename(std::string s)
{
	size_t pos = s.find_last_of("BUILD AVLTREE ");
	std::string filename = s.substr(pos + 1) + ".txt";
	return filename;
}

int AVLTree::ExtractNumber(std::string s)
{
	std::string n = "";
	unsigned int i = 0;
	while (i <= s.length() - 1)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n += s[i];
		}
		i++;
	}
	int number = stoi(n);
	return number;
}
