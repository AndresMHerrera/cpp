#ifndef CONTAINER_INCLUDED
#define CONTAINER_INCLUDED
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include "trie.h"
#define MAX_LINES 20
#define EXPECTED_INPUT 2
#define SUFFIX 2
#define PREFIX 1
#define EXIT 3
#define INVALID_INPUT -1 //main menu
#define EXIT_EXPECTED_INPUT 1
#define START 0 //main menu
#define INITIAL_INDEX 0
using namespace std;


struct lines
{
	vector<string> word;
};


struct pages
{
	vector<lines> line;
};


class container
{
private:
	vector<pages> lookup;
	std::map<string, int> map;

	//SUFFIX TRIE HERE
	trie suffixTree;
	//STANDARD TRIE HERE
	trie prefixTree;

public:
	container(char const *argv[]);
	~container();

	void vector_insertPattern(string pattern, int pageNumber, int lineNumber);
	void print_surroundingPatter(int pageNumber, int lineNumber, int wordNumber);

	void process_file(char const *argv[]);
	void process_page(vector<string> & lines,int page_count);
	void process_line(string line, int page_number, int line_number);
	string remove_nonAlphaNumberic(string token);
	string convert_to_upper(string input);

//map	
	void create_map();
	string trim_spaces_of_string(string input);

//user interface
int read_user_input(string &inputPattern);
void mainMenu();

//suffix search
void suffixSearch_Initialization(string inputPattern);

//prefix search
void prefixSearch_Initialization(string searchPattern); 	//mod 12.8

};

#endif