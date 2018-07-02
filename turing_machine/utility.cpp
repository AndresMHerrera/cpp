#include "utility.h"

//only L or R (upper or lower case)
bool is_valid_direction(string input)
{
    input = convert_to_upper(input);
    return ((input.length() == 1) && (input[0] == 'R' || input[0] == 'L')) ? true : false;
}

// Alphabets will consist of printable characters from ASCII character set, with exception of
// \
// [ and ]
// < and >
//white space characters are excluded from the alphabets
bool is_valid_alphabet(string input)
{
    return ((input.length() == 1) && (input[0] != '\\') 
            && (input[0] != '[') && (input[0] != ']') 
            && (input[0] != '<') && (input[0] != '>') 
            && (input[0] >= '!') && (input[0] <= '~')) ? true : false;
}


//this method ensures that state name contains only specified characters
//upper/lower case letter ok
//digits ok
//underscores ok
bool is_valid_state_name_format(string input)
{
    int index = 0;
    bool result = true;

    while(index < (input.length())) {
        if(isdigit(input[index]) || isupper(input[index]) || islower(input[index]) || input[index] == '_')
            ++index;
        else
            return false;
    }

    return result;
}


//checks if string has colon at end
bool is_keyword_format(string input)
{
    return (input[input.length() - 1] == ':') ? true : false;
}


//will compare the validKeyword with input and return true if they are equal or not
bool is_valid_keyword(string input, string validKeyword)
{
    input = trim_leading_and_trailing_spaces_of_string(input);
    input = convert_to_upper(input);

    return (input == validKeyword) ? true : false;
}


string trim_leading_and_trailing_spaces_of_string(string input)
{
    input = trim_leading_spaces_of_string(input);
    input = trim_trailing_spaces_of_string(input);
    return input;
}

string trim_trailing_spaces_of_string(string input)
{
    string::iterator it = input.end() - 1;
    while(it != input.begin() - 1 && isspace(*it)) 
    {
        input.erase(it);
        it = input.end()-1;
    }

    return input;
}

string trim_leading_spaces_of_string(string input)
{
    string::iterator it = input.begin();

    while(it != input.end() && isspace(*it)) 
    {
        it = input.erase(it);
    }
   
    return input;
}

string convert_to_upper(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}
