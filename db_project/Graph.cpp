#include "Graph.h"

void Graph::Build(std::string filename)
{
	std::ifstream data(filename);

	// Calculate the maximum size of elements that are to
	// be inserted
	std::string numbers;
	while (std::getline(data, numbers))
		maxSize += 2;
	maxSize += 100; // add some extra space
	
	delete[] Elements; // delete for safety
	Elements = new Cell[maxSize];

	// Go to the start of the file
	data.clear();
	data.seekg(0, std::ios_base::beg);

	int i = 0;
	while (std::getline(data, numbers))
	{
		int a, b;
		ExtractNumbers(numbers, a, b);
		Insert(a, b);
	}
}

void Graph::Insert(std::string line)
{
	int a, b;
	ExtractNumbers(line, a, b);
	Insert(a, b);
}

void Graph::Insert(int a, int b)
{
	int indexA = FindIndex(a);
	int indexB = FindIndex(b);
	
	// Add as new node if it does not exist
	if (indexA == -1)
		indexA = AddNode(a);
	if (indexB == -1)
		indexB = AddNode(b);
	
	if (indexA != indexB)
	{
		Elements[indexA].next = AddLink(Elements[indexA].next, b);
		Elements[indexB].next = AddLink(Elements[indexB].next, a);
	}
	else
	{
		Elements[indexA].next = AddLink(Elements[indexA].next, b);
	}
	links++;
}

int Graph::AddNode(int n)
{
	// Returns the index at which the number was inserted
	nodes++;
	Elements[nodes - 1].value = n;
	return (nodes - 1);
}

int Graph::FindIndex(int n)
{
	int index = -1;
	for (int i = 0; i < nodes; i++)
	{
		if (n == Elements[i].value)
			index = i;
	}
	return index;
}

Cell* Graph::AddLink(Cell* cell, int value)
{
	if (cell != nullptr)
	{
		if (cell->value == value) // link already exists
		{
			links--; // just to counter the lines++ in the Connect function
			return cell;
		}
		cell->next = AddLink(cell->next, value);
	}
	else
		cell = new Cell(value);
	return cell;
}

bool Graph::Delete(std::string line)
{
	int a, b;
	ExtractNumbers(line, a, b);

	int indexA = FindIndex(a);
	int indexB = FindIndex(b);
	if (indexA == -1 || indexB == -1)
		return false; // one or both numbers not found

	if (RemoveLink(Elements[indexA], b))
	{
		RemoveLink(Elements[indexB], a);
		return true; // succesfully removed link
	}
	return false; // link does not exist
}

bool Graph::RemoveLink(Cell& cell, int value)
{
	if (cell.next != nullptr)
	{
		if (cell.next->value != value)
			return RemoveLink(*cell.next, value);
		else
		{
			// We found the link with the value we're looking for
			// and it's in the next cell from the one we're at now.
			// We need to remove it from the chain.
			Cell* temp = cell.next;
			cell.next = cell.next->next;
			delete temp;
			return true;
		}
	}
	return false;
}

void Graph::GetSize(int & n, int & l) const
{
	n = nodes;
	l = links;
}

void Graph::ExtractNumbers(std::string line, int & a, int & b)
{
	std::string n1 = "";
	std::string n2 = "";
	unsigned int i = 0;
	while (line[i] < '0' || line[i] > '9')
		i++; // find the first char that is a number
	// save the numbers to seperate strings and convert them to ints
	while ((i <= line.length() - 1) && (line[i] != ' '))
	{
		if (line[i] >= '0' && line[i] <= '9')
			n1 += line[i];
		i++;
	}
	while (i <= line.length() - 1)
	{
		if (line[i] >= '0' && line[i] <= '9')
			n2 += line[i];
		i++;
	}
	if (n1 != "")
		a = stoi(n1);
	if (n2 != "")
		b = stoi(n2);
}
