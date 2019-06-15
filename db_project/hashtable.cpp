#include "hashtable.h"

void Hashtable::Build(std::string filename)
{
	std::ifstream data(filename);

	std::string number = "";
	while (std::getline(data, number))
		elements++;

	capacity = 2 * elements + 1000;
	table = new cell[capacity];

	data.clear();
	data.seekg(0, std::ios_base::beg);

	while (std::getline(data, number))
	{

		int value = stoi(number);
		Insert(value, table);
	}
}

bool Hashtable::Insert(int value, cell* t)
{
	int index = HashFunction(value, capacity);
	if (t[index].right == nullptr)
		t[index].right = new cell{ value, nullptr };
	else
	{
		cell* currentCell = t[index].right;
		while (currentCell != nullptr)
		{
			if (currentCell->value == value)
				return false;
			currentCell = currentCell->right;
		}
		currentCell = new cell{ value, nullptr };
	}
	return true;
}


bool Hashtable::Insert(int number)
{
	double a = elements / capacity;
	if (a > 0.5)
	{
		ResizeTable();
	}
	if (Insert(number, table))
	{
		return true;
	}
	return false;
}

bool Hashtable::Delete(int number)
{
	int index = HashFunction(number, capacity);

	cell* currentCell = &table[index];
	cell* nextCell = currentCell->right;
	while (nextCell != nullptr)
	{
		if (nextCell->value == number)
		{
			elements--;
			currentCell->right = nextCell->right;
			delete nextCell;
			return true;
		}
		currentCell = nextCell->right;
		nextCell = currentCell->right;
	}
	return false;
}

bool Hashtable::Search(int number) const
{
	int index = HashFunction(number, capacity);
	cell* currentCell = table[index].right;
	while (currentCell != nullptr)
	{
		if (currentCell->value == number)
		{
			return true;
		}
		currentCell = currentCell->right;
	}
	return false;
}

int Hashtable::GetSize() const
{
	return elements;
}

cell * Hashtable::FindPosOfCell(int i, int x, cell * t)
{
	if (t[i].right == nullptr)
		return t[i].right;
	else
	{
		cell* currentCell = t[i].right;
		while (currentCell->right != nullptr)
		{
			if (currentCell->value == x)
				return currentCell;
			currentCell = currentCell->right;
		}
		return currentCell;
	}
}

int Hashtable::HashFunction(int x, int cap) const
{
	int i = ((17 * x + 55) % bucket) % cap;
	return i;
}

void Hashtable::ResizeTable()
{
	int newCapacity = 2 * capacity;
	cell *temp = new cell[newCapacity];
	for (int i = 0; i < capacity; i++)
	{
		cell* currentCell = table[i].right;
		while (currentCell != nullptr)
		{
			int value = currentCell->value;
			Insert(value, temp);
			currentCell = currentCell->right;
		}
	}
	capacity = newCapacity;
	delete[] table;
	table = temp;
}