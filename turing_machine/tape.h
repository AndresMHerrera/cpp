#ifndef TAPE_H
#define TAPE_H
#include "crash.h"
#include "direction.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <exception>

using namespace std;

class Tape
{
private:
    string cells;
    int current_cell;
    char blank;

public:
    Tape();                                         //INOUT parameters pass in as a reference
    void load(ifstream& definition , bool& valid);
    void view() const;
    void initialize(string input_string);
    void update(char write_character, DIRECTION move_direction);
    string left(int maximum_number_of_cells);
    string right(int maximum_number_of_cells);
    char current_character() const;
    char blank_character() const;
    bool is_first_cell() const;
};

#endif