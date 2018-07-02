#include "tape.h"
#include "utility.cpp"

Tape::Tape():
    cells(""),
    current_cell(0),
    blank(' ')
{}


//looks for blank character
void Tape::load(ifstream &definitionFile, bool &valid)
{

    valid = false;
    string token;
    bool blankSymbolFound_flag = false;
    int blank_character_count = 0;

    if(definitionFile.is_open())
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty())
            {
                if(is_keyword_format(token))
                {
                    if(is_valid_keyword(token, "FINAL_STATES:"))
                    {
                        if(blankSymbolFound_flag && blank_character_count == 1) {
                            valid = true;
                            return;
                        }
                        else if (!blankSymbolFound_flag || blank_character_count != 1) {
                            if(!blankSymbolFound_flag)
                                cout << "Error: missing blank character" << endl;
                            valid = false;
                            return;
                        }
                    }
                    else {
                        cout << "Error: invalid keyword = " << token << endl;
                        valid = false;
                        return;
                    }
                }
                else //it must be the blank symbol
                {
                    if ((token.length() == 1) && blankSymbolFound_flag == false &&
                        (token[0] != '\\') && (token[0] != '[') &&
                        (token[0] != ']') && (token[0] != '<') &&
                        (token[0] != '>') && (token[0] >= '!') &&
                        (token[0] <= '~')) 
                    { 
                        this->blank = token[0];
                        blankSymbolFound_flag = true;
                    }
                    else {
                        cout << "Error: Illegal/multipe blank characters.\n";
                        valid = false;
                    }
                    blank_character_count++;
                }
            }
        }
    }
    
    cout << "Error: blank character/FINAL_STATES keyword is missing" << endl;
}


void Tape::view() const
{
    cout << "B = " << this->blank << "\n";
}

void Tape::initialize(string input_string)
{
    cells = input_string + blank;
    current_cell = 0;
}

/*
* Description:This function will update the tape.
*
* Input: <input vars>
*
* Ouput: <expected output>
*/
void Tape::update(char write_character, DIRECTION move_direction)
{
    move_direction = toupper(move_direction);

    if ((move_direction == 'L') && (current_cell == 0)) {
      //  return;
        throw  Crash("left move from first cell");
    }
    if ((move_direction == 'R') && (current_cell == cells.length() - 1)) {
        cells += blank; //possible error -- out of storage
    }

    cells[current_cell] = write_character;

    if ((move_direction == 'L')) {
        --current_cell;
    }
    else {
        ++current_cell;
    }
}


string Tape::left(int maximum_number_of_cells)
{
    //done to ensure a non-negative number
    int first_cell = max(0, current_cell - maximum_number_of_cells); //max defined in <algorithm>
    string value = cells.substr(first_cell, current_cell - first_cell);

    if (value.length() < current_cell) {
        value.insert(0,"<");
    }
    return value;
}

string Tape::right(int maximum_number_of_cells)
{
    int end_cell = cells.length() - 1;

    while ((end_cell >= current_cell) && (cells[end_cell] == blank)) {
        --end_cell;
    }

    int last_cell = min(end_cell, current_cell + maximum_number_of_cells - 1);
    string value = cells.substr(current_cell, last_cell - current_cell + 1);

    if (value.length() < end_cell - current_cell + 1) {
        value.append(">");
    }

    return value;
}

char Tape::current_character() const
{
    return cells[current_cell];
}

char Tape::blank_character() const
{
    return blank;
}

bool Tape::is_first_cell() const
{
    return (current_cell == 0);
}
