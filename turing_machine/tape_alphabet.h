#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Tape_Alphabet
{
private:
    vector<char> alphabet;
public:
    bool is_element(char value);
    void view();
    void load(ifstream & definitionFile, bool & valid);    
    int size();
};


#endif
