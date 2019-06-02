#pragma once

#include <fstream>
#include <string>
#include <chrono>

/*
BUILD HASHTABLE
SEARCH HASHTABLE number
INSERT HASHTABLE number
DELETE HASHTABLE number
*/

struct cell
{
	int value = -1;
	cell *right = nullptr;
};

class Hashtable
{
    public:
		void BuildHashTable(std::string line, std::ofstream& output);
		bool Insert(int value, cell* t);
        void InsertNewNumber(std::string line, std::ofstream& output);
        void Delete(std::string line, std::ofstream& output);
		void Search(std::string line, std::ofstream& output);
		void GetSize(std::string line, std::ofstream& output);
		int HashFunction(int x, int cap);
		cell* FindPosOfCell(int i, int x, cell* t);

    private:
		cell *table = nullptr;
		int elements = 0;
		int capacity = 0;
        int bucket = 1572869;
		std::string ExtractFilename(std::string s);
		int ExtractNumber(std::string s);
		void ResizeTable();
};
