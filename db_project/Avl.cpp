#include "Avl.h"

Node::Node(int v, Node * l, Node * r)
{
	value = v;
	leftChild = l;
	rightChild = r;
}

// Recursive function that calculates the current
// height of a node at any time
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
}

bool AVLTree::Delete(int number)
{
	bool found = false;
	root = Delete(root, number, found);
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
	elements++;
	return n;
}

Node * AVLTree::Delete(Node* n, int value, bool& found)
{
	Node* temp = nullptr; // we'll save the node we need to delete here.
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
				// Since the node is a leaf we can just delete it.
				temp = n;
				n = nullptr;
			}
			else if (n->leftChild != nullptr && n->rightChild == nullptr) // Left child only
			{
				// When the node only has on child, it replaces its parent
				// that is going to get deleted
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
				// When the node has two children we can replace it with
				// the minimum node of its right subtree
				// After we need to delete the node tha we brought up.
				Node* replacingNode = MinNode(n->rightChild);
				n->value = replacingNode->value;
				n->rightChild = Delete(n->rightChild, replacingNode->value, found);
			}
			found = true;
			elements--;
			delete temp;
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
		return n; // Node already balanced

	if (nBalanceFactor > 1) // Height greater on the left subtree
	{
		// Now we need to calculate the balance factor of the child
		// so that we know what rotations we need to do
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
	else if (nBalanceFactor < -1) // Height greater on the right subtree
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
	// We navigate to the far left of the tree that
	// has root n
	Node* currentNode = n;
	if (currentNode != nullptr)
	{
		while (currentNode->leftChild != nullptr)
			currentNode = currentNode->leftChild;
		return currentNode;
	}
	else
		return n;
}

int AVLTree::GetSize() const
{
	return elements;
}

bool AVLTree::Search(int number) const
{
	// Starting from the root, we try to find the number
	// moving down the tree
	Node* currentNode = root;
	while (currentNode != nullptr)
	{
		if (currentNode->value == number)
			return true;
		if (number < currentNode->value)
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
	}
	return false;
}

int AVLTree::GetMin() const
{
	Node* minNode = MinNode(root);
	if (minNode != nullptr)
		return minNode->value;
	return -1;
}

int AVLTree::nodeBalanceFactor(Node * n)
{
	return (n->leftChild->height() - n->rightChild->height());
}
