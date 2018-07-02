#ifndef INITIAL_STATE_H
#define INITIAL_STATE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Initial_State
{
private:
    string initialState;

public:

    void load(ifstream & definitionFile, bool & valid);
    bool is_element(string value);
    void view();
    bool is_empty();
    string get();
    void set(string value);
};

#endif