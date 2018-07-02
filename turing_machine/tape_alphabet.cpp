#include "tape_alphabet.h"
#include "utility.cpp"

int Tape_Alphabet::size()
{
    return alphabet.size();
}

bool Tape_Alphabet::is_element(char value)
{
    for(vector<char>::iterator it = alphabet.begin(); it != alphabet.end(); ++it) 
    {
        if(*it == value)
            return true;
    }

    return false;  
}

void Tape_Alphabet::view()
{
    if (!alphabet.empty())
    {
        cout << "Gamma = {";
        for(vector<char>::iterator it = alphabet.begin(); it != alphabet.end(); ++it) 
        {
            if(it == alphabet.end() -1)
                cout << *it << "}" << endl;
            else
                cout << *it << ", ";
        }
    }
    cout << endl;
}

void Tape_Alphabet::load(ifstream & definitionFile, bool & valid)
{
    bool allValidAlphabet_flag = true;    
    valid = false;
    string token;

    //first line read should contain the keyword wanted
    if(definitionFile.is_open()) 
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty()) 
            {
                if(is_keyword_format(token))
                {
                    //will return when next keyword is reached, check for validity
                    if(is_valid_keyword(token, "TRANSITION_FUNCTION:"))
                    {
                        if(allValidAlphabet_flag && alphabet.size() >= 1)
                        {
                            valid = true;
                            return;
                        }

                        else
                        {
                            if(alphabet.size() < 1)
                                cout << "Error: Tape Alphabet is empty" << endl;
                            valid = false;
                            return;
                        }
                    }
                    else
                    {
                        cout << "Error: invalid keyword = " << token << endl;
                        valid = false;
                        return;
                    }
                }

                else //it must be alphabet and unique
                {
                    if (is_valid_alphabet(token) && !this->is_element(token[0]))
                        alphabet.push_back(token[0]);
                    else 
                    { //not valid
                        allValidAlphabet_flag = false;
                        cout << "Error: missing/invalid alphabet character" << endl;
                    }
                }
            }//end if statement
        }//end outer while
    }//end file open

cout << "Error: missing/invalid alphabet and/or TRANSITION_FUNCTION keyword" << endl;
}

