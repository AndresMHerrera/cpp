#ifndef STRING_SERVICE_INCLUDED
#define STRING_SERVICE_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

class StringService
{
public:	

	StringService();
	~StringService();
	
	string & ltrim(std::string &s);
	string & rtrim(std::string &s);
	string & trimLeadingAndTrailingSpaces(string &s);



};

#endif