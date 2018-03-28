#include "string.service.h"

StringService::StringService(){}

StringService::~StringService(){}

/****************************************************************************
Description: This function will trim leading and trailing spaces of a std::string.
output: returns a string
****************************************************************************/
string StringService::trimLeadingAndTrailingSpaces(string input)
{
	char * copy = new char[input.size()+1];//+1 is for '\0'

	strcpy(copy, input.c_str());

	//point to first element
	char * start = copy;

	//point to last
	char * end = NULL;

    // trim leading blank spaces off the line
    while ((isspace(*start) || *start == '\t') && (*start != '\0')) {
		start++;
		if (*start == '\0')
			continue;
	}

	// Trim trailing space
    end = start + strlen(start) - 1;

    while (end > start && isspace(*end)) {
    	end--;
    }

    // Write new null terminator
    *(end+1) = '\0';

    int length = strlen(start);
	char array[length];
	int i = 0;

	//copy content of pointer to array
	for(i = 0; i <= length; i++) {
		array[i] = start[i];
	}

	//convert to std::string and return it
	string temp(array);
	input = temp;

	delete [] copy;

	return input;
}