#include <fstream>
#include <chrono>
#include "MaxHeap.h"
#include "MinHeap.h"
#include "hashtable.h"
#include "Avl.h"

bool IsCommand(std::string command, std::string line)
{
	return (line.find(command) != std::string::npos);
}

std::string ExtractFilename(std::string command, std::string line)
{
	size_t pos = line.find_last_of(command);
	std::string filename = line.substr(pos + 1) + ".txt";
	return filename;
}

int ExtractNumber(std::string line)
{
	std::string n = "";
	unsigned int i = 0;
	while (i <= line.length() - 1)
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			n += line[i];
		}
		i++;
	}
	int number = -1;
	if (n != "")
		number = stoi(n);
	return number;
}

int main()
{
	std::ifstream commands("commands.txt");
	std::ofstream output("output.txt");

	MaxHeap maxH;
	MinHeap minH;
	Hashtable hashT;
	AVLTree avlTree;

	std::string line = "";
	while (std::getline(commands, line))
	{
		auto start = std::chrono::steady_clock::now();

		int number = ExtractNumber(line);
		output << std::endl << line << "\t\t";
		
		if (IsCommand("BUILD MAXHEAP", line))
		{
			std::string filename = ExtractFilename("BUILD MAXHEAP ", line);
			maxH.Build(filename);
		}
		else if (IsCommand("INSERT MAXHEAP", line))
		{
			if (maxH.Insert(number))
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS FULL";
				continue;
			}
		}
		else if (IsCommand("FINDMAX MAXHEAP", line))
		{
			int max = maxH.GetMax();
			if (max != -1)
				output << max;
			else
				output << "HEAP IS EMPTY";
			continue;
		}
		else if (IsCommand("DELETEMAX MAXHEAP", line))
		{
			if (maxH.DeleteMax())
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("GETSIZE MAXHEAP", line))
		{
			int size = maxH.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		else if (IsCommand("BUILD MINHEAP", line))
		{
			std::string filename = ExtractFilename("BUILD MINHEAP ", line);
			minH.Build(filename);
		}
		else if (IsCommand("INSERT MINHEAP", line))
		{
			if (minH.Insert(number))
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS FULL";
				continue;
			}
		}
		else if (IsCommand("FINDMIN MINHEAP", line))
		{
			int min = minH.GetMin();
			if (min != -1)
				output << min;
			else
			output << "HEAP IS EMPTY";
			continue;
		}
		else if (IsCommand("DELETEMIN MINHEAP", line))
		{
			if (minH.DeleteMin())
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("GETSIZE MINHEAP", line))
		{
			int size = minH.GetSize();
			output << size << " ELEMENTS - ";
			continue;
		}

		else if (IsCommand("BUILD HASHTABLE", line))
		{
			std::string filename = ExtractFilename("BUILD HASHTABLE ", line);
			hashT.Build(filename);
		}
		else if (IsCommand("INSERT HASHTABLE", line))
		{
			if (hashT.Insert(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER ALREADY EXISTS - ";
		}
		else if (IsCommand("DELETE HASHTABLE", line))
		{
			if (hashT.Delete(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("SEARCH HASHTABLE", line))
		{
			if (hashT.Search(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("GETSIZE HASHTABLE", line))
		{
			int size = hashT.GetSize();
			output << size << " ELEMENTS - ";
			continue;
		}

		else if (IsCommand("BUILD AVLTREE", line))
		{
			std::string filename = ExtractFilename("BUILD AVLTREE ", line);
			avlTree.Build(filename);
		}
		else if (IsCommand("FINDMIN AVLTREE", line))
		{
			int min = avlTree.GetMin();
			if (min != -1)
				output << "\t" << min << " - ";
			else
			{
				output << "AVL TREE IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("INSERT AVLTREE", line))
		{
			avlTree.Insert(number);
		}
		else if (IsCommand("DELETE AVLTREE", line))
		{
		;
		}
		else if (IsCommand("SEARCH AVLTREE", line))
		{
			if (avlTree.Search(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("GETSIZE AVLTREE", line))
		{
			int size = avlTree.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		double elapsedTime = elapsed_seconds.count() * 1000;
		output << elapsedTime << " ms";
	}
	return 0;
}