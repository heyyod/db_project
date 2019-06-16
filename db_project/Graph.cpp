#include "Graph.h"

void Graph::Build(std::string filename)
{
	std::ifstream data(filename);

	std::string numbers;
	while (std::getline(data, numbers))
		maxSize += 2;
	maxSize += 100;
	
	delete[] Elements;
	Elements = new Cell[maxSize];

	// Go to the start of the file
	data.clear();
	data.seekg(0, std::ios_base::beg);

	int i = 0;
	while (std::getline(data, numbers))
	{
		int a, b;
		ExtractNumbers(numbers, a, b);
		Connect(a, b);
	}
}

void Graph::Connect(std::string line)
{
	int a, b;
	ExtractNumbers(line, a, b);
	Connect(a, b);
}

void Graph::Connect(int a, int b)
{
	int indexA = FindIndex(a);
	int indexB = FindIndex(b);
	if (indexA == -1)
		indexA = Insert(a);
	if (indexB == -1)
		indexB = Insert(b);
	
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

int Graph::Insert(int n)
{
	// returns the index in which the number was inserted
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
		if (cell->value == value) // connection already exists
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
		return true;
	}
	return false;
}

bool Graph::RemoveLink(Cell& cell, int value)
{
	if (cell.next != nullptr)
	{
		if (cell.next->value != value)
			return RemoveLink(*cell.next, value);
		else
		{
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
		i++;
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
