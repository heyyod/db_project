#include "MinHeap.h"

MinHeap::~MinHeap()
{
	delete[] heap;
}

void MinHeap::BuildMinHeap(std::string line, std::ofstream& output)
{
	auto start = std::chrono::steady_clock::now();

	auto filename = ExtractFilename(line);
	std::ifstream data(filename);

	std::string number = "";
	while (std::getline(data, number))
		currentSize++;

	maxSize = currentSize + 100;
	delete[] heap;
	heap = new int[maxSize];

	data.clear();
	data.seekg(0, std::ios_base::beg);

	// Fill the heap
	heap[0] = -1;
	int i = 1;
	while (std::getline(data, number))
	{
		int element = std::stoi(number);
		heap[i] = element;
		i++;
	}

	for (int i = currentSize / 2; i >= 1; i--)
	{
		Heapify(i);
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	double elapsedTime = elapsed_seconds.count() * 1000;
	output << line << "\t\t" << elapsedTime << " ms.\n";
}

void MinHeap::Heapify(int level)
{
	int parent = heap[level];
	int leftPos = leftChild(level);
	int rightPos = rightChild(level);
	int minPos = level;

	if (leftPos <= currentSize)
	{
		if (parent > heap[leftPos])
			minPos = leftPos;

		if (rightPos <= currentSize)
			if (heap[minPos] > heap[rightPos])
				minPos = rightPos;
	}

	if (minPos != level)
	{
		Swap(minPos, level);
		Heapify(minPos);
	}
}

void MinHeap::Swap(int i, int j)
{
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

void MinHeap::GetSize(std::string line, std::ofstream& output) const
{
	output << line << "\t\t" << currentSize << " elements\n";
}

void MinHeap::GetMax(std::string line, std::ofstream& output) const
{
	int min = heap[1];
	if (currentSize)
	{
		output << line << "\t\t" << min << "\n";
	}
	else
	{
		output << line << "\t\tERROR - HEAP IS EMPTY";
	}
}

void MinHeap::Insert(std::string line, std::ofstream& output) //TODO: change parametre to string
{
	if (currentSize == maxSize)
	{
		output << line << "\t\tERROR - HEAP IS FULL";
	}
	else
	{
		auto start = std::chrono::steady_clock::now();

		int n = ExtractNumber(line);
		int pos = ++currentSize;
		heap[pos] = n;

		while (pos > 1 && heap[parent(pos)] > heap[pos])
		{
			Swap(pos, parent(pos));
			pos = parent(pos);
		}

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		double elapsedTime = elapsed_seconds.count() * 1000 * 1000;
		output << line << "\t\t" << elapsedTime << " ms\n";
	}
}

void MinHeap::DeleteMax(std::string line, std::ofstream& output)
{
	if (currentSize == 0)
	{
		output << line << "\t\tERROR - HEAP IS EMPTY";
	}
	else
	{
		auto start = std::chrono::steady_clock::now();

		int temp = heap[currentSize--];
		int tempPos = 1;
		int newPos = 1;
		heap[1] = temp;

		while (tempPos < currentSize)
		{
			int leftC = leftChild(tempPos);
			int rightC = rightChild(tempPos);
			if (leftC <= currentSize)
			{
				if (temp > heap[leftC])
					newPos = leftC;

				if (rightC <= currentSize)
					if (heap[leftC] > heap[rightC])
						newPos = rightC;
			}

			if (newPos != tempPos)
			{
				Swap(tempPos, newPos);
				tempPos = newPos;
			}
			else
				break;
		}
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		double elapsedTime = elapsed_seconds.count() * 1000;
		output << line << "\t\t" << elapsedTime << " ms\n";
	}
}

int MinHeap::parent(int i)
{
	return i / 2;
}

int MinHeap::leftChild(int parentPos)
{
	return 2 * parentPos;
}

int MinHeap::rightChild(int parentPos)
{
	return (2 * parentPos) + 1;
}

int MinHeap::ExtractNumber(std::string s)
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
	int number = std::stoi(n);
	return number;
}

std::string MinHeap::ExtractFilename(std::string s)
{
	size_t pos = s.find_last_of("BUILD MINHEAP ");
	std::string filename = s.substr(pos + 1) + ".txt";
	return filename;
}
