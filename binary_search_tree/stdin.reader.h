#ifndef STDIN_READER_INCLUDED
#define STDIN_READER_INCLUDED

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <vector>
#define END_READING_INDICATOR "END"
#define SUCCESS true
#define NO_SUCCESS false
#define FIRST 0
#define SECOND 1
#define CASE_1 '0'
#define CASE_2 '\0'
#define CASE_3 '-'
using namespace std;

class STDinReaderService
{
public:
	vector<int> read_stdin();
private:
	int process_input(string input);
};

#endif