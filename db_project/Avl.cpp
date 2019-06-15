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

void AVLTree::Build(std::string filename)
{
	std::ifstream data(filename);

	std::string number;
	while (std::getline(data, number))
	{
		int x = std::stoi(number);
		Insert(x);
	}
}

void AVLTree::Insert(int number)
{
	root = Insert(root, number);
	elements += 1;
}

Node* AVLTree::Insert(Node* n, int value)
{
	if (n == nullptr)
	{
		Node* n = new Node(value, nullptr, nullptr);
		return n;
	}
	else if (value <= n->value)
	{
		n->leftChild = Insert(n->leftChild, value);
	}
	else
	{
		n->rightChild = Insert(n->rightChild, value);
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
		bool isLeftLeftCase = (n->leftChild->leftChild != nullptr);
		if (isLeftLeftCase) // LEFT LEFT
		{
			return RightRotation(n);
		}
		else // LEFT RIGHT
		{
			n->leftChild = LeftRotation(n->leftChild);
			return RightRotation(n);
		}
	}
	else if (nBalanceFactor < -1)
	{
		bool isRightRightCase = (n->rightChild->rightChild != nullptr);
		if (isRightRightCase) // RIGHT RIGHT
		{
			return LeftRotation(n);
		}
		else // RIGHT LEFT
		{
			n->rightChild = RightRotation(n->rightChild);
			return LeftRotation(n);
		}
	}
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

int AVLTree::GetSize() const
{
	return elements;
}

bool AVLTree::Search(int number) const
{
	Node* currentNode = root;
	while (currentNode != nullptr)
	{
		if (currentNode->value == number)
		{
			return true;
		}
		if (number < currentNode->value)
		{
			currentNode = currentNode->leftChild;
		}
		else
		{
			currentNode = currentNode->rightChild;
		}
	}
	return false;
}

int AVLTree::GetMin() const
{
	Node* currentNode = root;
	if (currentNode != nullptr)
	{
		while (currentNode->leftChild != nullptr)
		{
			currentNode = currentNode->leftChild;
		}
		return currentNode->value;
	}
	else
	{
		return -1;
	}
}

int AVLTree::nodeBalanceFactor(Node * n)
{
	return (n->leftChild->height() - n->rightChild->height());
}
