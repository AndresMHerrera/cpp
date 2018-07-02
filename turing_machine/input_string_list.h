#ifndef STRING_LIST_H
#define STRING_LIST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Input_String_List
{
private:
    vector<string> input_string_list;
public:
    
    string extract_string(int index);
    void insert_string(string input_string);
    bool is_string_in_list(string input_string);
    void remove_string(int index);
    int size();
};

#endif
