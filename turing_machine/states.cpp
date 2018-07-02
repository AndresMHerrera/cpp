#include "states.h"
#include "utility.cpp"

States::States()
{}

/*
* Description:This constructor will insert a new state into the vector of states
*
* Input: name of state to be inserted
*
* Ouput: no ouput. list of states will be 1. 
*/
States::States(string state_name)
{
    state_names.push_back(state_name);
}

// /*
// * Description:This function will determine if a given input state is
// *             part of the list of states.
// * Input: name of state to be checked for validity.
// *
// * Ouput: Will return true if it is part of the list of states, else false
//         will be returned.
// */      
bool States::is_element(string value)
{
    vector<string>::iterator it = state_names.begin();
    while(it != state_names.end())
    {
        if (*it == value)
            return true;
        ++it;
    }

    return false;
}

int States::total_number_of_states()
{   
    return state_names.size();
}

//prints comma separated
void States::view()
{
    cout << "Q = {";
    for(vector<string>::iterator it = state_names.begin(); it != state_names.end(); ++it) 
    {
        cout << *it;

        if (it == state_names.end() - 1)
            cout << "}" << endl;
        else
            cout << ", ";
    }    
}


//assume file is open
//assume that previous component that read file checked that the keyword for this read
//  exists. 
// > will continue reading from start of information
// > check that next keyword exists and is valid
// > keywords can be upper or lower case
// > white spaces as delimeters btwn groups of chars
// > even if error is found keep processing just to find all errors
// > assumes file is not eof
// THERE MUST BE AT LEAST 1 STATE
void States::load(ifstream & definitionFile, bool & valid)
{

    bool allValidStates_flag = true;
    valid = false;
    string token;

    if(definitionFile.is_open()) 
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            //process currentLine
            //first token should be the keyword
            if(!token.empty()) 
            {
                if (is_keyword_format(token))
                {
                    //check if its next valid keyword, if not, error(will return if in here)
                    if(is_valid_keyword(token, "INPUT_ALPHABET:"))
                    {
                        if(allValidStates_flag) {
                            valid = true;
                            return;
                        }
                        else {
                            valid = false;
                            return;
                        }
                    }
                    else //error, something other than keyword or state
                    {
                        //must be a state with colon or different keyword, invalid print error
                        valid = false;
                        allValidStates_flag = false;
                        cout << "Error: missing/invalid states" << endl;
                    }
                }//end keyword format token

                else  //not a keyword therefore a state
                {
                    if (is_valid_state_name_format(token))
                    {
                        //check that it is unique
                        if (!is_element(token))
                        {
                            state_names.push_back(token);
                        }
                        else //not unique
                        {
                            valid = false;
                            allValidStates_flag = false;
                            cout << "Error: duplicate states" << endl;
                        }
                    }
                    else
                    {
                        allValidStates_flag = false;
                        cout << "Error: state name format invalid" << endl;
                    }
                }             
            }//end if statement
        }//end outer while
    }//end file open

cout << "Error: missing/invalid States and/or INPUT_ALPHABET keyword" << endl;
}