#include "hash_table.h"

/****************************************************************************
Description: Will allocate memory for the hash table and initialize private
			members.
output: none.
****************************************************************************/
hash_table::hash_table()
{
	table = new hash_node *[HASH_TABLE_SIZE];

	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{

		table[i] = NULL;
	}
}

/****************************************************************************
Description: Destructor will free all memory allocated during runtime,
			includes hash nodes, and hash table
output: none.
****************************************************************************/
hash_table::~hash_table()
{
	//delete hash nodes
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{

		if (table[i] != NULL)
			delete table[i];
	}

	//delete table
	delete[] table;
}

/****************************************************************************
Description: This function will insert a new hash value into the hast table.
output: none.
****************************************************************************/
void hash_table::insert_hash_value(char insert_key, double insert_value)
{
	//hash function
	int hash_index = hash_function(insert_key);

	table[hash_index] = new hash_node;
	table[hash_index]->key = insert_key;
	table[hash_index]->value = insert_value;
}

/****************************************************************************
Description: This function will calculate the index given a character input.
			index is calculated by taking the characters ascii value and
			subtracting 65.

output: hash table index
****************************************************************************/
int hash_table::hash_function(char insert_value)
{
	return insert_value - SUBTRACT_VALUE;
}

//will retrieve and return the mass, given a char input
/****************************************************************************
Description: This function will retrieve and return the mass, given a 
			characters input.

output: Will return the monoisotopic mass of the character.
****************************************************************************/
double hash_table::get_hash_value(char input)
{
	return table[hash_function(input)]->value;
}

void hash_table::printHashTable()
{
	cout << "\nPrinting Hash Table" << endl;
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		if (this->table[i] != NULL) {
			cout << "key:" << this->table[i]->key << ", value:" << this->table[i]->value << endl;
		}
	}
	cout << endl;
}