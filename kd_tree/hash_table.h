#ifndef HASH_TABLE_INCLUDED
#define HASH_TABLE_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#define HASH_TABLE_SIZE 27
#define SUBTRACT_VALUE 65
using namespace std;

struct hash_node
{
	char   key;
	double value;
};

class hash_table
{
private:
	hash_node ** table;

public:	

	hash_table();
	~hash_table();
	void insert_hash_value(char insert_key, double insert_value);
	int hash_function(char insert_value);
	double get_hash_value(char input);
	void printHashTable();
};

#endif