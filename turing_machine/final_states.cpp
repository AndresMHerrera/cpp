#include "final_states.h"
#include "utility.cpp"

Final_States::Final_States()
{ }

bool Final_States::is_element(string value)
{
    if(!names.empty())
    {
        vector<string>::iterator it = names.begin();
        while(it != names.end())
        {
            if (*it == value)
                return true;
            ++it;
        }
    }

    return false;
}

//possible for no final states
void Final_States::load(ifstream & definitionFile, bool & valid)
{
    valid = true;
    string token;
    bool s;
    if(definitionFile.is_open()) 
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty()) 
            {
               if (is_valid_state_name_format(token))
                {                    
                    //check that it is unique
                    if (!is_element(token))
                    {
                        names.push_back(token);
                    }
                    else //not unique
                    {
                        valid = false;
                        cout << "Error: duplicate states" << endl;
                    }
                }
                else
                {
                    valid = false;
                    cout << "Error: state name format invalid" << endl;
                }                      
            }
        }
    }
}

void Final_States::view()
{
    cout << "F = {";
    if(!names.empty())
    {
       for(vector<string>::iterator it = names.begin(); it != names.end(); ++it) 
        {
            cout << *it;

            if (it == names.end() - 1)
                cout <<  "}" << endl;
            else
                cout << ", ";
        }
    }
    else
        cout << "}" << endl;
}

int Final_States::size()
{
    return names.size();
}

string Final_States::element(int index)
{
    if(!names.empty())
        return this->names[index];
    else
        return "";
}
