#include "transition_function.h"
#include "utility.cpp"


void Transition_Function::view() const
{
    cout << "Transition Functions" << endl;
    for(vector<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); ++it)
    {
        cout << "Delta(" << it->source_state() << ",";
        cout << it->read_character() << ") = (";
        cout << it->destination_state() << ",";
        cout << it->write_character() << ",";
        cout << it->move_direction() << ")" << endl;
    }
    cout << endl;
}

int Transition_Function::size() const
{
    return transitions.size();
}

string Transition_Function::source_state(int index) const
{
    return transitions[index].source_state();
}

char Transition_Function::read_character(int index) const
{
    return transitions[index].read_character();
}

string Transition_Function::destination_state(int index) const
{
    return transitions[index].destination_state();
}

char Transition_Function::write_character(int index) const
{
    return transitions[index].write_character();
}

bool Transition_Function::is_defined_transition(string source_state,
                                                char read_character,
                                                string & destination_state,
                                                char & write_character,
                                                DIRECTION & move_direction) const
{
    for(int index = 0; index < transitions.size(); ++index)
    {
        if ((transitions[index].source_state() == source_state
            && (transitions[index].read_character() == read_character)))
        {
            destination_state = transitions[index].destination_state();
            write_character = transitions[index].write_character();
            move_direction = transitions[index].move_direction();
            return true;
        }
    }
    return false;
}

bool Transition_Function::is_source_state(string state) const
{
    for(vector<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); ++it) 
    {   
        if (it->source_state() == state)
            return true;
    }
    return false;
}

// it is possible to have no transitions
// ◦ note: take care of the case where TM only has 1 state and 0 transitions
// • each transition must use legal states and tape characters
// • the direction in a transition must be specified in the file as “L” or “R” (upper or lower case)
// • in the definition file we have at most one transition from a state on a given tape character,since
// TM is deterministic
// ◦ transitions must be unique
// • If a state is defined to be a final state, no transitions allowed from that state
//first word read should be the keyword
//return when keyword format word is found
//there can be 0 transitions
void Transition_Function::load(ifstream & definitionFile, bool & valid)
{
    //flags
    valid = false;    
    bool s_flag = false;
    bool r_flag = false;
    bool d_flag = false;
    bool w_flag = false;
    bool m_flag = false;
    bool allValidTransitions_flag = true;
    string s,r,d,w,m;

    string token;

    //first line read should contain the keyword wanted
    if(definitionFile.is_open()) 
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty()) 
            {
                if(is_keyword_format(token))
                {
                    //will return when next keyword is reached, check for validity
                    if(is_valid_keyword(token, "INITIAL_STATE:"))
                    {
                        if(allValidTransitions_flag) 
                        {
                            valid = true;
                            return;
                        }
                        else //there can be 0 transitions therefore dont check vector size
                        {
                            valid = false;
                            return;
                        }
                    }
                    else {
                        cout << "Error: invalid keyword = " << token << endl;
                        valid = false;
                        return;
                    }
                }

                else //it must be a transition component
                {
                    if (s_flag == false && is_valid_state_name_format(token))
                    {
                        s_flag = true; s = token;
                    }
                    else if (s_flag && r_flag == false && is_valid_alphabet(token))
                    {
                        r_flag = true; r = token[0];
                    }
                    else if (s_flag && r_flag && d_flag == false && is_valid_state_name_format(token))
                    {
                        d_flag = true; d = token;
                    }
                    else if (s_flag && r_flag && d_flag && w_flag == false && is_valid_alphabet(token))
                    {
                        w_flag = true; w = token[0];
                    }
                    else if (s_flag && r_flag && d_flag && w_flag && m_flag == false && is_valid_direction(token))
                    {
                        m_flag = true; m = token[0];
                        if (s_flag && r_flag && d_flag && w_flag && m_flag && is_unique_transition(s,r[0],d,w[0],m[0]))
                        {
                            transitions.push_back(Transition(s,r[0],d,w[0],m[0]));
                            s_flag = false; r_flag = false, d_flag = false; w_flag = false; m_flag = false;
                        }
                        else //should never reach here if file is valid
                        {
                                allValidTransitions_flag = false;
                                cout << "Error: missing/invalid/duplicate transition function" << endl;
                        }
                    } 
                }          
            }//end if statement
        }//end outer while
    }//end file open
cout << "Error: TRANSITION_FUNCTION keyword missing" << endl;   
}

/*
* Description:This function will compare the new transition to the rest to verify that it is unique
*
* Input: new transition information
*
* Ouput: returns true if new transition is unique, else false. 
*/
bool Transition_Function::is_unique_transition(string i_source, char i_read,
                                                string i_destination, char i_write, DIRECTION i_move)
{
    if (!transitions.empty())
    {
        //traverse all transitions and compare;
        int i = 0;
        while(i < transitions.size()) 
        {
            if((transitions[i].source_state() == i_source) 
                && (transitions[i].read_character() == i_read)
                && (transitions[i].destination_state() == i_destination)
                && (transitions[i].write_character() == i_write) 
                && (transitions[i].move_direction() == i_move))
            {
                return false;
            }

            //ensures 1 transition from a given state on a given character
            if((transitions[i].source_state() == i_source) 
                && (transitions[i].read_character() == i_read))
            {
                return false;
            }

            ++i;
        }

        return true;
    }
    else
        return true; //if empty then new transition will be unique
}
