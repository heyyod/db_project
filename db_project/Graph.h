#pragma once
#include <string>
#include <fstream>

/*
COMPUTESHORTESTPATH N1 N2
COMPUTESPANNINGTREE
FINDCONNECTEDCOMPONENTS
*/

struct Cell
{
	Cell()
	{
		value = -1;
		next = nullptr;
	}
	Cell(int v)
	{
		value = v;
		next = nullptr;
	}
	int value;
	Cell* next;
};

class Graph
{
public:
	bool Build(std::string filename);
	bool Insert(std::string line);
	bool Delete(std::string line);
	void GetSize(int& n, int& l) const;
	int ConnectedComponents();
	
private:
	int AddNode(int n);
	int FindIndex(int n);
	bool Insert(int a, int b);
	Cell* AddLink(Cell* cell, int value);
	bool RemoveLink(Cell& cell, int value);
	void DepthFirstSearch(int index, bool* visited);

private:
	Cell* Elements = nullptr;
	int nodes = 0;
	int links = 0;
	int maxSize = 0;

	void ExtractNumbers(std::string line, int& a, int& b);
};