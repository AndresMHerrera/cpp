#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include "states.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "transition_function.h"
#include "initial_state.h"
#include "tape.h"
#include "final_states.h"
#include "crash.h"
#include <exception>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Turing_Machine
{
private:
    States states;
    Input_alphabet input_alphabet;
    Tape_Alphabet tape_alphabet;
    Transition_Function transition_function;
    Initial_State initial_state;
    Tape tape;
    Final_States final_states;

    vector<string> description;
    string current_state;
    string original_input_string;
    int number_of_transitions;
    bool valid;
    bool used;
    bool operating;
    bool accepted;
    bool rejected;

public:
    Turing_Machine();
    Turing_Machine(string definition_file_name);
    void view_definition();
    void view_instantaneous_description(int maximum_number_of_cells);
    void initialize(string input_string);
    void perform_transitions(int maximum_number_of_transitions);
    void terminate_operation();
    string input_string() const;
    int total_number_of_transitions() const;
    bool is_valid_definition() const;
    bool is_valid_input_string(string value);
    bool is_used() const;
    bool is_operating() const;
    bool is_accepted_input_string() const;
    bool is_rejected_input_string() const;

    bool read_definition_file(string definitionFile);
    void load(ifstream &definitionFile, bool &valid);
    bool is_valid_input_alphabet();
    bool is_valid_final_states();
    bool final_states_have_transition();

};
    
#endif