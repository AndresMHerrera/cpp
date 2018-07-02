#ifndef TRANSITION_H
#define TRANSITION_H

#include "direction.h"
#include <string>
#include <iostream>
using namespace std;

class Transition
{
private:
    string    source;
    char      read;
    string    destination;
    char      write;
    DIRECTION move;

public:
    Transition(string    source_state,
               char      read_character,
               string    destination_state,
               char      write_character,
               DIRECTION move_direction);

    string    source_state()      const; //const to guarantee that the private members will not be modified
    char      read_character()    const;
    string    destination_state() const;
    char      write_character()   const;
    DIRECTION move_direction()    const;
};

#endif