#pragma once

#include <fstream>
#include <string>

class MaxHeap
{
public:
	~MaxHeap();
	void Build(std::string filename);
	int GetSize() const;
	int GetMax() const;
	bool Insert(int number);
	bool DeleteMax();

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