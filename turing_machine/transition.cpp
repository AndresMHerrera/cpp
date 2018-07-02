#include "transition.h"

Transition::Transition(string Source_state,
                       char Read_character,
                       string Destination_state,
                       char Write_character,
                       DIRECTION Move_direction):
        source(Source_state),
        read(Read_character),
        destination(Destination_state),
        write(Write_character),
        move(Move_direction)
{ }

string Transition::source_state() const
{
    return source;
}

char Transition::read_character() const
{
    return read;
}

string Transition::destination_state() const
{
    return destination;
}

char Transition::write_character() const
{
    return write;
}

DIRECTION Transition::move_direction() const
{
    return move;
}