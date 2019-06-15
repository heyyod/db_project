#pragma once

#include <fstream>
#include <string>

class MinHeap
{
public:
	~MinHeap();
	void Build(std::string filename);
	int GetSize() const;
	int GetMin() const;
	bool Insert(int number);
	bool DeleteMin();

private:
	void Heapify(int size);
	void Swap(int i, int j);
	int parent(int i);
	int leftChild(int parentPos);
	int rightChild(int parentPos);

private:
	int currentSize = 0;
	int maxSize = 0;
	int *heap = nullptr;
};