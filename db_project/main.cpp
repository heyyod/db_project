#include <fstream>
#include <chrono>
#include "MaxHeap.h"
#include "MinHeap.h"
#include "hashtable.h"
#include "Avl.h"
#include "Graph.h"

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

	MaxHeap maxHeap;
	MinHeap minHeap;
	Hashtable hashTable;
	AVLTree avlTree;
	Graph graph;

	std::string line = "";
	while (std::getline(commands, line))
	{
		auto start = std::chrono::steady_clock::now();

		int number = ExtractNumber(line);
		output << std::endl << line << "\t\t";
		
		//~~~~~~~~~~~~~~~ MAX HEAP ~~~~~~~~~~~~~~~
		if (IsCommand("BUILD MAXHEAP", line))
		{
			std::string filename = ExtractFilename("BUILD MAXHEAP ", line);
			maxHeap.Build(filename);
		}
		else if (IsCommand("INSERT MAXHEAP", line))
		{
			if (maxHeap.Insert(number))
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS FULL";
				continue;
			}
		}
		else if (IsCommand("FINDMAX MAXHEAP", line))
		{
			int max = maxHeap.GetMax();
			if (max != -1)
				output << max;
			else
				output << "HEAP IS EMPTY";
			continue;
		}
		else if (IsCommand("DELETEMAX MAXHEAP", line))
		{
			if (maxHeap.DeleteMax())
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("GETSIZE MAXHEAP", line))
		{
			int size = maxHeap.GetSize();
			output << size << " ELEMENTS";
			continue;
		}

		//~~~~~~~~~~~~~~~ MIN HEAP ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD MINHEAP", line))
		{
			std::string filename = ExtractFilename("BUILD MINHEAP ", line);
			minHeap.Build(filename);
		}
		else if (IsCommand("INSERT MINHEAP", line))
		{
			if (minHeap.Insert(number))
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS FULL";
				continue;
			}
		}
		else if (IsCommand("FINDMIN MINHEAP", line))
		{
			int min = minHeap.GetMin();
			if (min != -1)
				output << min;
			else
			output << "HEAP IS EMPTY";
			continue;
		}
		else if (IsCommand("DELETEMIN MINHEAP", line))
		{
			if (minHeap.DeleteMin())
				output << "SUCCESS - ";
			else
			{
				output << "HEAP IS EMPTY";
				continue;
			}
		}
		else if (IsCommand("GETSIZE MINHEAP", line))
		{
			int size = minHeap.GetSize();
			output << size << " ELEMENTS - ";
			continue;
		}

		//~~~~~~~~~~~~~~~ HASHTABLE ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD HASHTABLE", line))
		{
			std::string filename = ExtractFilename("BUILD HASHTABLE ", line);
			hashTable.Build(filename);
		}
		else if (IsCommand("INSERT HASHTABLE", line))
		{
			if (hashTable.Insert(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER ALREADY EXISTS - ";
		}
		else if (IsCommand("DELETE HASHTABLE", line))
		{
			if (hashTable.Delete(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("SEARCH HASHTABLE", line))
		{
			if (hashTable.Search(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
		}
		else if (IsCommand("GETSIZE HASHTABLE", line))
		{
			int size = hashTable.GetSize();
			output << size << " ELEMENTS - ";
			continue;
		}

		//~~~~~~~~~~~~~~~ AVL TREE ~~~~~~~~~~~~~~~
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
			if (avlTree.Delete(number))
				output << "SUCCESS - ";
			else
				output << "NUMBER NOT FOUND - ";
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

		//~~~~~~~~~~~~~~~ GRAPH ~~~~~~~~~~~~~~~
		else if (IsCommand("BUILD GRAPH", line))
		{
			std::string filename = ExtractFilename("BUILD GRAPH ", line);
			graph.Build(filename);
		}
		else if (IsCommand("GETSIZE GRAPH", line))
		{
			int nodes, links;
			graph.GetSize(nodes, links);
			output << nodes << " NODE, " << links << " LINKS";
			continue;
		}
		else if (IsCommand("INSERT GRAPH", line))
		{
			graph.Connect(line);
		}
		else if (IsCommand("DELETE GRAPH", line))
		{
			if (graph.Delete(line))
				output << "SUCCESS - ";
			else
				output << "NUMBERS OR LINK NOT FOUND - ";
		}

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		double elapsedTime = elapsed_seconds.count() * 1000;
		output << elapsedTime << " ms";
	}
	return 0;
}