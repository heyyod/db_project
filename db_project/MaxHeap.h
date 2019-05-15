#pragma once

#include <fstream>
#include <string>
#include <chrono>
#include <iostream>

class MaxHeap
{
public:
	~MaxHeap();
	void BuildMaxHeap(std::string line, std::ofstream& output);
	void Heapify(int size);
	void Swap(int i, int j);
	void GetSize(std::ofstream& output) const;
	void GetMax(std::ofstream& output) const;
	void Insert(std::string s, std::ofstream& output);
	void DeleteMax(std::ofstream& output);

	int parent(int i);
	int leftChild(int parentPos);
	int rightChild(int parentPos);

private:
	int ExtractNumber(std::string s);
	std::string ExtractFilename(std::string s);
	int currentSize = 0;
	int maxSize = 0;
	int *heap = nullptr;
};