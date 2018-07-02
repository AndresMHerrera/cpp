#include "turing_machine.h"
#include "utility.cpp"

Turing_Machine::Turing_Machine()
{
    valid = false;
    operating = false;
    accepted = false;
    rejected = false;
    number_of_transitions = 0;    
}
/*
* Description:This constructor will initialize all attributes of the class
*
* Input: path to turing machine definition file
*
* Ouput: all members will be initialized
*/
Turing_Machine::Turing_Machine(string definition_file_name)
{
    //absolete
}

/*
* Description:This function will be the driver for reading the different sections
*           of the definition file.
* Input: path to the definition file
*
* Ouput: returns true if all information was read successfully, else returns false
*/
bool Turing_Machine::read_definition_file(string definitionFile) //still need to check when not valid
{
    valid = false;
    bool finaldecision = true;
    ifstream file;
    file.open(definitionFile.c_str(), ios_base::in);

    if(file.is_open())
    {
        this->load(file, valid);
        if (!valid){
            finaldecision = valid;
        }

        states.load(file,valid);

       if (!valid){
            finaldecision = valid;
        }

        input_alphabet.load(file,valid);

       if (!valid){
            finaldecision = valid;
        }

        tape_alphabet.load(file,valid);

        if(!is_valid_input_alphabet())
            finaldecision = false;

       if (!valid){ 
            finaldecision = valid;
        }

        transition_function.load(file,valid);

           if (!valid){
            finaldecision = valid;
        }

        initial_state.load(file,valid);

         if (!valid){
            finaldecision = valid;
        }
        if(!states.is_element(initial_state.get())){
            finaldecision = false;
            cout << "Error: Initial state not in set of States." << endl;
        }

        tape.load(file,valid);

          if (!valid){
            finaldecision = valid;
        }

        if(input_alphabet.is_element(tape.blank_character()))
        {
            cout << "Error: Input alphabet contains blank character" << endl;
            finaldecision = false;
        }

        final_states.load(file,valid);

        if (!valid)
            finaldecision = valid;

        if(!is_valid_final_states() == true)
            finaldecision = false;

        //check that final state has no transitions
        if (final_states_have_transition())
        {
            finaldecision = false;   
        }

        valid = finaldecision;
        return finaldecision;
    }
    else
        return valid;

}

/*
* Description:This function will traverse the transition function list to determine if a final state has a 
*transition.
* Input: no input
*
* Ouput: return true if there is a transition with a final state as a source state.
*/
bool Turing_Machine::final_states_have_transition()
{
    if (final_states.size() != 0) //not empty
    {
        for (int i = 0; i < final_states.size(); ++i)
        {
            if(transition_function.is_source_state(final_states.element(i))) {
                cout << "Error: final state has transition." << endl;
                return true;
            }
        }

        return false;
    }
    else
        return false; //final state has no transitions
}


/*
* Description:This function will check that final states are part of the set of states
*
* Input: none
*
* Ouput: returns true if all final states are in set of states else false. 
*/
bool Turing_Machine::is_valid_final_states()
{
    int i = 0;
    if(final_states.size() == 0)
        return true;
    if(final_states.size() > states.total_number_of_states())
        return false;

    while(i < final_states.size()) 
    {
        if(!states.is_element(final_states.element(i))) 
        {
            cout << "Error: Not all final states are a part of set of states." << endl;
            return false;
        }
        ++i;
    }
    
    return true;
}

/*
* Description:This function will check that input alphabet is in tape alphabet
*
* Input: none
*
* Ouput: returns true if input alphabet is in tape alphabet, false otherwise
*/
bool Turing_Machine::is_valid_input_alphabet()
{
    int i = 0;
    if(tape_alphabet.size() < input_alphabet.size())
        return false;

    while(i < input_alphabet.size() && i < tape_alphabet.size()) 
    {
        if(!tape_alphabet.is_element(input_alphabet.element(i))) 
        {
            cout << "Error: Input alphabet not in tape alphabet." << endl;
            return false;
        }
        ++i;
    }
    
    return true;
}

/*
* Description:This function will read its portion of the turing machine definition file.
*
* Input: file object, and boolean valid flag
*
* Ouput: valid is set to true if read was successful.
*/
void Turing_Machine::load(ifstream &definitionFile, bool &valid)
{
    valid = false;
    string token;

    if(definitionFile.is_open())
    {
        while(definitionFile >> token)
        {
            token = trim_leading_and_trailing_spaces_of_string(token);

            if(!token.empty())
            {
                if(is_valid_keyword(token, "STATES:"))
                {
                    valid = true;
                    return;
                }
                else //it must be the blank symbol
                {
                    description.push_back(token);
                }
            }
        }
    }  
    cout << "Error: STATES keyword is missing or invalid" << endl;
}

/*
* Description:This function will display all information pertaining to the
*           turing machine definition file.     
* Input: no input
*
* Ouput: will display definition of turing machine to user. OK
*/
void Turing_Machine::view_definition() 
{
    if (!description.empty())
    {
        for(int i = 0; i < description.size(); ++i) 
        {
            if(i == description.size() - 1)
                cout << description[i] << " " << endl;
            else
                cout << description[i] << " ";
        }
    }
    cout << endl;

    this->states.view();
    this->input_alphabet.view();
    tape_alphabet.view();
    transition_function.view();
    initial_state.view();
    tape.view();
    final_states.view();

}


void Turing_Machine::view_instantaneous_description(int maximum_number_of_cells)
{
    cout << number_of_transitions << ".";
    cout << tape.left(maximum_number_of_cells);
    cout << "[" << current_state << "]" << tape.right(maximum_number_of_cells) << endl;
}

/*
* Description:This function will initialize the turing machine to a given input string.
*
* Input: <input vars>
*
* Ouput: <expected output>
*/
void Turing_Machine::initialize(string input_string)
{
    if (valid)
    {
        current_state = initial_state.get();
        original_input_string = input_string;
        tape.initialize(input_string);
        used = true;
        operating = true;
        accepted = false;
        rejected = false;
        number_of_transitions = 0;
    }    
}

//must not be zero
void Turing_Machine::perform_transitions(int maximum_number_of_transitions)
{
    string destination_state;
    char write_character;
    DIRECTION move_direction;

    if (final_states.is_element(initial_state.get())) //accept if initial state is also final state
    {
        accepted = true;
        this->terminate_operation();
        return;
    }

    for(int i = 0; i < maximum_number_of_transitions; ++i)
    {
        if (transition_function.is_defined_transition(current_state, tape.current_character(),
                                                    destination_state, write_character, move_direction))
        {
            ++number_of_transitions;
            current_state = destination_state;

            try
            {
                tape.update(write_character, move_direction);
            }
            catch(exception & error)
            {
                cout << error.what() << ".\n";
                this->terminate_operation();
            }

            if (final_states.is_element(current_state))
            {
                accepted = true;
            }

        }
        else //transition not defined
        {
            if(accepted) {
                this->terminate_operation();
                return;
            }
            else
            {
                rejected = true;
                this->terminate_operation();
                return;
            }
        }
    }
}

void Turing_Machine::terminate_operation()
{
    if (operating)
    {
        operating = false;
        cout << "Input string " << original_input_string << " ";
        if (accepted && !rejected)
        {
            cout << "is accepted in " << number_of_transitions << " transitions." << endl;
        }
        else if (!accepted && rejected)
        {
            cout << "is rejected in " << number_of_transitions << " transitions." << endl;
        }
        else//not accepted and not rejected
        {
            cout << "not accepted or rejected in " << number_of_transitions << " transitions." << endl;
        }
    }
    else //not operating on input string
    {
        cout << "Not running on an input string. " << endl;
    }
}

string Turing_Machine::input_string() const
{
    return original_input_string;
}

int Turing_Machine::total_number_of_transitions() const
{
    return number_of_transitions;
}

bool Turing_Machine::is_valid_definition() const
{
    return valid;
}

bool Turing_Machine::is_valid_input_string(string value)
{
    if(!value.empty())
    {
        for(int i = 0; i < value.size(); ++i) 
        {
            if(!input_alphabet.is_element(value[i]))
                return false;

        }
        return true;
    }
    else
        return false;
}

bool Turing_Machine::is_used() const
{
    return used;
}

bool Turing_Machine::is_operating() const
{
    return operating;
}

bool Turing_Machine::is_accepted_input_string() const
{
    return accepted;
}

bool Turing_Machine::is_rejected_input_string() const
{
    return rejected;
}