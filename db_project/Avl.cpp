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
	if (this != nullptr) 
	{
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

bool AVLTree::Delete(int number)
{
	bool found = false;
	root = Delete(root, number, found);
	if(found)
		elements -= 1;
	return found;
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

Node * AVLTree::Delete(Node* n, int value, bool& found)
{
	Node* temp = nullptr;
	if (n != nullptr)
	{
		if (value < n->value)
			n->leftChild = Delete(n->leftChild, value, found);
		else if (value > n->value)
			n->rightChild = Delete(n->rightChild, value, found);
		else
		{
			if (n->leftChild == nullptr && n->rightChild == nullptr) // No children
			{
				temp = n;
				n = nullptr;
			}
			else if (n->leftChild != nullptr && n->rightChild == nullptr) // Left child only
			{
				Node* leftChild = n->leftChild;
				temp = n;
				n = leftChild;
			}
			else if (n->leftChild == nullptr && n->rightChild != nullptr) // Right child only
			{
				Node* rightChild = n->rightChild;
				temp = n;
				n = rightChild;
			}
			else // Left and Right child
			{
				Node* replacingNode = MinNode(n->rightChild);
				n->value = replacingNode->value;
				n->rightChild = Delete(n->rightChild, replacingNode->value, found);
			}
			delete temp;
			found = true;
		}
	}
	n = BalanceNode(n);
	return n;
}

Node* AVLTree::BalanceNode(Node* n)
{
	if (n == nullptr)
		return n;

	int nBalanceFactor = nodeBalanceFactor(n);

	if (nBalanceFactor >= -1 && nBalanceFactor <= 1)
	{
		return n;
	}

	if (nBalanceFactor > 1)
	{
		int leftBalanceFactor = nodeBalanceFactor(n->leftChild);
		if (leftBalanceFactor >= 0) // LEFT LEFT
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
		int rightBalanceFactor = nodeBalanceFactor(n->rightChild);
		if (rightBalanceFactor <= 0) // RIGHT RIGHT
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

Node * AVLTree::MinNode(Node * n) const
{
	Node* currentNode = n;
	if (currentNode != nullptr)
	{
		while (currentNode->leftChild != nullptr)
		{
			currentNode = currentNode->leftChild;
		}
		return currentNode;
	}
	else
	{
		return n;
	}
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
	Node* minNode = MinNode(root);
	if (minNode != nullptr)
	{
		return minNode->value;
	}
	return -1;
}

int AVLTree::nodeBalanceFactor(Node * n)
{
	return (n->leftChild->height() - n->rightChild->height());
}
