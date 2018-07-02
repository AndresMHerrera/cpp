#include "input_alphabet.h"
#include "utility.cpp"

char Input_alphabet::element(int index)
{
    if(!alphabet.empty())
        return alphabet[index];
    else
        return '\0';
}

bool Input_alphabet::is_element(char value)
{
    for(vector<char>::iterator it = alphabet.begin(); it != alphabet.end(); ++it) 
    {
        if(*it == value)
            return true;
    }

    return false;
}

int Input_alphabet::size()
{
    return alphabet.size();
}

void Input_alphabet::view()
{
    if (!alphabet.empty())
    {
        cout << "Sigma = {";
        for(vector<char>::iterator it = alphabet.begin(); it != alphabet.end(); ++it) 
        {
            if(it == alphabet.end() -1)
                cout << *it << "}" << endl;
            else
                cout << *it << ", ";
        }
    }
    else
        cout << "Sigma = {}" << endl;
}


// Alphabets will consist of printable characters from ASCII character set, with exception of
// \
// [ and ]
// < and >
//white space characters are excluded from the alphabets
//characters in a alphabet must be unique
//every character in the input alphabet must be in the tape alphabet (check for this outside of this)
//the blank symbol must not be in the input alphabet
void Input_alphabet::load(ifstream & definitionFile, bool & valid)
{
    bool allValidAlphabet_flag = true;    
    valid = false;
    string token;

    //first line read should contain the keyword wanted
    if(definitionFile.is_open()) 
    {
        //while(!definitionFile.eof())
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty()) 
            {
                if(is_keyword_format(token))
                {
                    //will return when next keyword is reached, check for validity
                    if(is_valid_keyword(token, "TAPE_ALPHABET:"))
                    {
                        if(allValidAlphabet_flag)
                        {
                            valid = true;
                            return;
                        }

                        else //there can be 0 elements, therefore no need to check size of vector
                        {
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

cout << "Error: TAPE_ALPHABET keyword missing" << endl;
}
