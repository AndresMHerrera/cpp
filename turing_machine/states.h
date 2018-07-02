#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class States
{
private:
    vector<string> state_names;

public:
    States();
    States(string state_name);
    bool is_element(string value);
    int total_number_of_states();
    void load(ifstream & definitionFile, bool & valid);
    void view();
};

#endif