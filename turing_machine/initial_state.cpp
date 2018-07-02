#include "initial_state.h"
#include "utility.cpp"


void Initial_State::load(ifstream & definitionFile, bool & valid)
{
    bool oneState_flag = true;    
    valid = false;
    string token;


    bool keywordMissingMessageDisplayed_flag = false;

    if(definitionFile.is_open()) 
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty()) 
            {
                if (is_keyword_format(token))
                {
                    //check if its next valid keyword, if not, error(will return if in here)
                    if(is_valid_keyword(token, "BLANK_CHARACTER:"))
                    {
                        if(oneState_flag && !initialState.empty()) {
                            valid = true;
                            return;
                        }
                        else {
                            cout << "Error: missing/invalid information (initial state)" << endl;
                            valid = false;
                            return;
                        }
                    }
                    else //error, something other than keyword or state
                    {
                        //must be a state with colon or different keyword, invalid print error
                        valid = false;
                        oneState_flag = false;
                        cout << "Error: invalid information (initial state) = " << token << endl;
                    }
                }//end keyword format token

                else  //not a keyword therefore a state
                {
                    if (is_valid_state_name_format(token) && oneState_flag)
                    {
                        //check that there is not a state there already
                        if (initialState.empty())
                        {
                            initialState = token;
                        }
                        else //theres already an initial state
                        {
                            valid = false;
                            oneState_flag = false;
                            cout << "Error: initial state already exists" << endl;
                        }
                    }
                    else
                    {
                        oneState_flag = false;
                        valid = false;
                        cout << "Error: invalid information (initial state)" << endl;
                    }
                }             
            }//end if statement
        }//end outer while
    }//end file open

cout << "Error: missing/invalid initial state and/or BLANK_CHARACTER keyword" << endl;    
}

bool Initial_State::is_element(string value)
{
    return (value == initialState) ? true : false;
}

void Initial_State::view()
{
    cout << "Initial state = " << initialState << endl;
}

bool Initial_State::is_empty()
{
    return initialState.empty();
}

string Initial_State::get()
{
    return initialState;
}

void Initial_State::set(string value)
{
    initialState = value;
}