#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "transition.h"
#include "direction.h"

using namespace std;

class Transition_Function
{
private:
vector<Transition> transitions;

public:
    void load(ifstream & definitionFile, bool & valid);
    void view() const;
    int size() const;
    string source_state(int index) const;
    char read_character(int index) const;
    string destination_state(int index) const;
    char write_character(int index) const;
    bool is_defined_transition(string      source_state,
                               char        read_character,
                               string &    destination_state,
                               char &      write_character,
                               DIRECTION & move_direction) const;
    bool is_source_state(string state) const;
  bool is_unique_transition(string i_source, char i_read,
                            string i_destination, char i_write, DIRECTION i_move);

};
#endif