#ifndef FINAL_STATES_H
#define FINAL_STATES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Final_States
{
private:
    vector<string> names;

public:
    Final_States();
    bool is_element(string value);
    void load(ifstream & definitionFile, bool & valid);
    void view();
    int size();
    string element(int index);

};

#endif