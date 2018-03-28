#ifndef STRING_SERVICE_INCLUDED
#define STRING_SERVICE_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

class StringService
{
public:	

	StringService();
	~StringService();
    string trimLeadingAndTrailingSpaces(string input);
};

#endif