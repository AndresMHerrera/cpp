#include "input_string_list.h"

string Input_String_List::extract_string(int index)
{
    int size = input_string_list.size();

    if(!input_string_list.empty() && index >= 0 && index <= (size - 1))
        return input_string_list[index];
    else
        return "";
}

void Input_String_List::insert_string(string input_string)
{
    input_string_list.push_back(input_string);
}

bool Input_String_List::is_string_in_list(string input_string)
{
    for(int i = 0; i < input_string_list.size(); ++i) {
        
        if (input_string_list[i] == input_string)
        {
            return true;
        }
    }
    return false;
}

void Input_String_List::remove_string(int index)
{
    int size = input_string_list.size();
    string temp;

    if(!input_string_list.empty() && index >= 0 && index <= (size - 1))
    {
        //if its the last element
        if(input_string_list[input_string_list.size()-1] == input_string_list[index])
            input_string_list.pop_back();
        else 
        {
            //save last element
            temp = input_string_list[input_string_list.size()-1];

            //put element to delete in last position
            input_string_list[input_string_list.size()-1] = input_string_list[index];

            //recover last element
            input_string_list[index] = temp;

            input_string_list.pop_back();
        }
    }
}

int Input_String_List::size()
{
    return input_string_list.size();
}