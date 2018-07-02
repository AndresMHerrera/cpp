#ifndef INPUT_ALPHABET_H
#define INPUT_ALPHABET_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Input_alphabet
{
private:
    vector<char> alphabet;
public:
    char element(int index);
    bool is_element(char value);
    void load(ifstream & definitionFile, bool & valid);
    int size();
    void view();
};


#endif
