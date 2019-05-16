#include <fstream>
#include <chrono>
#include "MaxHeap.h"
#include "MinHeap.h"

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
			maxH.GetMax(output);
		}
		else if (IsCommand("GETSIZE MAXHEAP",line))
		{
			maxH.GetSize(output);
		}
		else if (IsCommand("DELETEMAX MAXHEAP",line))
		{
			maxH.DeleteMax(output);
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
			minH.GetMax(output);
		}
		else if (IsCommand("GETSIZE MINHEAP", line))
		{
			minH.GetSize(output);
		}
		else if (IsCommand("DELETEMIN MINHEAP", line))
		{
			minH.DeleteMax(output);
		}
	}

	return 0;
}