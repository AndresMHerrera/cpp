#include "container.h"

//this function will be used to initialize the suffix search
void container::suffixSearch_Initialization(string inputPattern)
{
	//will return a vector of words that will be printed on the terminal
	vector<print_object> storage = suffixTree.suffix_search_start(inputPattern);

	//print each object, and its surrounding patterns
	for (int i = 0; i < storage.size(); ++i)
	{
		print_surroundingPatter(storage[i].page,storage[i].line,storage[i].word);
	}

}

//this function will  be used to initialize the prefix search
void container::prefixSearch_Initialization(string searchPattern)
{
	//will return a vector of words that will be printed on the terminal
	vector<print_object> storage = prefixTree.prefix_search_start(searchPattern);

	//print each object, and its surrounding patterns
	for (int i = 0; i < storage.size(); ++i)
	{
		print_surroundingPatter(storage[i].page,storage[i].line,storage[i].word);
	}

}
