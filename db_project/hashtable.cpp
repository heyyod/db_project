#include "hashtable.h"

void Hashtable::BuildHashTable(std::string line, std::ofstream& output)
{
	auto start = std::chrono::steady_clock::now();

	auto filename = ExtractFilename(line);
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

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	double elapsedTime = elapsed_seconds.count() * 1000;
	output << line << "\t\t" << elapsedTime << " ms\n";
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


void Hashtable::InsertNewNumber(std::string line, std::ofstream& output)
{
	auto start = std::chrono::steady_clock::now();

	std::string result = "NUMBER INSERTED SUCCESSFULLY";
	int x = ExtractNumber(line);
	double a = elements / capacity;
	if (a > 0.5)
	{
		ResizeTable();
	}
	if (!Insert(x, table))
		result = "NUMBER ALREADY EXISTS";
	else
		elements++;

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	double elapsedTime = elapsed_seconds.count() * 1000;
	output << line << "\t\t" << elapsedTime << " ms " << result << "\n";
}

void Hashtable::Delete(std::string line, std::ofstream& output)
{
	auto start = std::chrono::steady_clock::now();

	std::string result = "ERROR - NUMBER NOT FOUND";
	int x = ExtractNumber(line);
	int index = HashFunction(x, capacity);

	cell* currentCell = &table[index];
	cell* nextCell = currentCell->right;
	while (nextCell != nullptr)
	{
		if (nextCell->value == x)
		{
			result = "DELETED SUCCESSFULLY";
			elements--;
			currentCell->right = nextCell->right;
			delete nextCell;
			break;
		}
		currentCell = nextCell->right;
		nextCell = currentCell->right;
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	double elapsedTime = elapsed_seconds.count() * 1000;
	output << line << "\t\t" << elapsedTime << " ms " << result << "\n";
}

void Hashtable::Search(std::string line, std::ofstream & output)
{
	auto start = std::chrono::steady_clock::now();

	std::string result = "FAILURE";
	int x = ExtractNumber(line);
	int index = HashFunction(x, capacity);
	cell* currentCell = table[index].right;
	while (currentCell != nullptr)
	{
		if (currentCell->value == x)
		{
			result = "SUCCESS";
			break;
		}
		currentCell = currentCell->right;
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	double elapsedTime = elapsed_seconds.count() * 1000;
	output << line << "\t\t" << elapsedTime << " ms " << result << "\n";
}

void Hashtable::GetSize(std::string line, std::ofstream & output)
{
	output << line << "\t\t" << elements << " elements\n";
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

int Hashtable::HashFunction(int x, int cap)
{
	int i = ((17 * x + 55) % bucket) % cap;
	return i;
}

std::string Hashtable::ExtractFilename(std::string s)
{
	size_t pos = s.find_last_of("BUILD HASHTABLE ");
	std::string filename = s.substr(pos + 1) + ".txt";
	return filename;
}

int Hashtable::ExtractNumber(std::string s)
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