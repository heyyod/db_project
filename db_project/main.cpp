#include <fstream>
#include <chrono>
#include "MaxHeap.h"
#include "MinHeap.h"
#include "hashtable.h"

bool IsCommand(std::string command, std::string line)
{
	return (line.find(command) != std::string::npos);
}

int main()
{
	std::ifstream commands("commands.txt");
	std::ofstream output("output.txt");

	MaxHeap maxH;
	MinHeap minH;
	Hashtable hashT;

	std::string line = "";
	while (std::getline(commands, line))
	{
		if (IsCommand("BUILD MAXHEAP", line))
		{
			maxH.BuildMaxHeap(line, output);
		}
		else if (IsCommand("INSERT MAXHEAP", line))
		{
			maxH.Insert(line, output);
		}
		else if (IsCommand("FINDMAX MAXHEAP",line))
		{
			maxH.GetMax(line, output);
		}
		else if (IsCommand("GETSIZE MAXHEAP",line))
		{
			maxH.GetSize(line, output);
		}
		else if (IsCommand("DELETEMAX MAXHEAP",line))
		{
			maxH.DeleteMax(line, output);
		}
		else if (IsCommand("BUILD MINHEAP", line))
		{
			minH.BuildMinHeap(line, output);
		}
		else if (IsCommand("INSERT MINHEAP", line))
		{
			minH.Insert(line, output);
		}
		else if (IsCommand("FINDMIN MINHEAP", line))
		{
			minH.GetMax(line, output);
		}
		else if (IsCommand("GETSIZE MINHEAP", line))
		{
			minH.GetSize(line, output);
		}
		else if (IsCommand("DELETEMIN MINHEAP", line))
		{
			minH.DeleteMax(line, output);
		}
		else if (IsCommand("BUILD HASHTABLE", line))
		{
			hashT.BuildHashTable(line, output);
		}
		else if (IsCommand("INSERT HASHTABLE", line))
		{
			hashT.InsertNewNumber(line, output);
		}
		else if (IsCommand("DELETE HASHTABLE", line))
		{
			hashT.Delete(line, output);
		}
		else if (IsCommand("SEARCH HASHTABLE", line))
		{
			hashT.Search(line, output);
		}
		else if (IsCommand("GETSIZE HASHTABLE", line))
		{
			hashT.GetSize(line, output);
		}
	}

	return 0;
}