#include "user_interface.h"

User_Interface::User_Interface() 
{}

User_Interface::~User_Interface() {}

bool User_Interface::loadFiles(string definitionFile_path, string stringFile_path, string TM_name)
{
    tm_name = TM_name;
    if(turing_machine.read_definition_file(definitionFile_path))
    {   
        cout << "Successfully Loaded Turing Machine!" << endl;
        read_from_string_file(stringFile_path);
        return true;
    }
    else
        return false;
}


void User_Interface::programFlowControl(string stringFile_path)
{
    bool exitFlag = false;

    while(exitFlag == false) {
        cout << endl;
        switch(CommandPrompt())        
        {
            case 'D':
                this->DeleteCommand();
                break;
            case 'X':
                this->ExitCommand(stringFile_path);
                exitFlag = true;
                break;
            case 'H':
                this->HelpCommand();
                break;
            case 'I':
                this->InsertCommand();
                break;
            case 'L':
                this->ListCommand();
                break;
            case 'Q':
                this->QuitCommand();
                break;
            case 'R':
                this->RunCommand();
                break;
            case 'E':
                this->SetCommand();
                break; 
            case 'W':
                this->ShowCommand();
                break;
            case 'T':
                this->TruncateCommand();
                break;
            case 'V':
                this->ViewCommand();
                break;
            case '\t':
                break;
            default:
                cout << "Invalid Command" << endl;
                break;
        }
        cout << endl;
        if (configuration_settings.is_help_enabled() && exitFlag == false)
        {
            this->ViewCommandDescription();
        }
    }
}

//assumes correct input command
char User_Interface::CommandPrompt()
{
    string inputCommand;
    char validCommand = '\0';

    cout << "Command: ";
    getline(cin,inputCommand);

    if (inputCommand.size() == 1)
    {   
        validCommand = toupper(inputCommand[0]);
    }
    
    if (inputCommand.empty())
        validCommand = '\t';

    return validCommand;
}

void User_Interface::QuitCommand()
{
    turing_machine.terminate_operation();
}

void User_Interface::RunCommand()
{
    // cout << "Input string number : 4" << endl;
    // cout << "0. [s0]AAABB" << endl;
    // cout << "5. XA[s1]AYB" << endl;
    string input;
    int index;
    bool flag = false;

    if (configuration_settings.is_help_enabled())
    {
       cout << "Enter the digit of the correspoding string from the input";
       cout << " string list." << endl;
    }
    if(!turing_machine.is_operating())
    {
        cout << "Input String Number: ";
        getline(cin, input,'\n');
        cout << endl;

        if(is_valid_digit(input))
        {
            istringstream (input) >> index; //user sees list starting at 1
            index += -1;          

            if(index < input_string_list.size() && index >= 0)
            {
                //success
                flag = true;
            }

            else 
            {
                cout << "Invalid Input string number." << endl; 
                return;
            }
        }
    }

    if(!turing_machine.is_operating() && flag)
    {
        turing_machine.initialize(input_string_list.extract_string(index));
        turing_machine.view_instantaneous_description(configuration_settings.get_maximum_number_of_cells());
        turing_machine.perform_transitions(configuration_settings.get_maximum_number_of_transitions());
        if(turing_machine.is_operating())
            turing_machine.view_instantaneous_description(configuration_settings.get_maximum_number_of_cells());                
    }
    else if(turing_machine.is_operating())//it is operating
    {
        turing_machine.perform_transitions(configuration_settings.get_maximum_number_of_transitions());
        if(turing_machine.is_operating())
            turing_machine.view_instantaneous_description(configuration_settings.get_maximum_number_of_cells());                
    }
}

//ok
void User_Interface::TruncateCommand()
{
    // cout << "Maximum number of cells[32] : 50" << endl;
    // cout << "Success!" << endl;
    string input;
    int value;

    if (configuration_settings.is_help_enabled())
    {
       cout << "Enter a value to change the setting for the maximum number of cells to left";
       cout << " and right of the tape head to display a Instantaneous description" << endl;
    }
    cout << "Maximum number of cells [" << configuration_settings.get_maximum_number_of_cells();
    cout << "]: ";
    getline(cin, input,'\n');
    cout << endl;

    if (!input.empty() && is_valid_digit(input))
    {
        istringstream (input) >> value;
        configuration_settings.set_maximum_number_of_cells(value);
        cout << "Success!" << endl;
    }
    if (!input.empty() && !is_valid_digit(input))
    {
        cout << "Error: Invalid Value" << endl;
    }
}

//ok
void User_Interface::SetCommand()
{
    // cout << "Maximum number of Transitions[1] : 4" << endl;
    // cout << "Settings changed!" << endl;
    string input;
    int value;

    if (configuration_settings.is_help_enabled())
    {
       cout << "Enter a value to change the setting for the maximum number of Transitions";
       cout << " to perform at a time during operation of Turing Machine" << endl;
    }
    cout << "Maximum number of transitions [" << configuration_settings.get_maximum_number_of_transitions();
    cout << "]: ";
    getline(cin, input,'\n');
    cout << endl;

    if (!input.empty() && is_valid_digit(input))
    {
        istringstream (input) >> value;
        configuration_settings.set_maximum_number_of_transitions(value);
        cout << "Success!" << endl;
    }
    if (!input.empty() && !is_valid_digit(input))
    {
        cout << "Error: Invalid Value" << endl;
    }    
}


void User_Interface::DeleteCommand()
{
    // cout << "Input String Number : 3" << endl;
    // cout << "String Deleted" << endl;
   string input;
   int index;

    if (configuration_settings.is_help_enabled())
    {
       cout << "Enter the digit of the correspoding string from the input";
       cout << " string list to be deleted." << endl;
    }
    cout << "Input String Number: ";
    getline(cin, input,'\n');
    cout << endl;

    if(is_valid_digit(input))
    {
        istringstream (input) >> index; //user sees list starting at 1
        index += -1;                    //because list is 0 based
        if(index < input_string_list.size() && index >= 0)
        {
            input_string_list.remove_string(index);
            cout << "String deleted!" << endl;
        }
        else //invalid number
            cout << "Input string number is invalid." << endl;
    }
    else
        cout << "Invalid Input string number." << endl;    
}


//ok
void User_Interface::InsertCommand()
{
    // cout << "Input String : AABB" << endl;
    // cout << "Input String Inserted!" << endl;
    string input;

    if (configuration_settings.is_help_enabled())
    {
       cout << "Enter a string that will be inserted into the input string list" << endl;
    }
    cout << "Input String: ";
    getline(cin, input,'\n');
    cout << endl;

    if(input.size() == 1 && input[0] == '\\' && !input_string_list.is_string_in_list(""))
    {
        input_string_list.insert_string("");
        cout << "Input string inserted!" << endl;
    }

    else if(turing_machine.is_valid_input_string(input))
    {
        if(!input_string_list.is_string_in_list(input)) 
        {
            input_string_list.insert_string(input);
            cout << "Input string inserted!" << endl;
        }
        else //already in list
            cout << "String already in list" << endl;
    }
    else
        cout << "Invalid Input string" << endl;
}

//ok
void User_Interface::ListCommand()
{
    if (input_string_list.size() != 0)
    {
        for(int i = 0; i < input_string_list.size(); ++i) 
        {
            if(input_string_list.extract_string(i) == "")
                cout << i+1 << ". " << '\\' << endl;
            else
                cout << i+1 << ". " << input_string_list.extract_string(i) << endl;
        }
    }
    else
        cout << "List is Empty!" << endl;
}

//ok
void User_Interface::ViewCommand()
{
    turing_machine.view_definition();
}



void User_Interface::ShowCommand()
{
    cout << "Course       : " << "Cpts 322 - Software Engineering Principles I" << endl;
    cout << "Semester     : " << "Spring" << endl;
    cout << "Year         : " << "2015" << endl;
    cout << "Instructor   : " << "Neil B. Corrigan" << endl;
    cout << "Author       : " << "Andres Herrera" << endl;
    cout << "Version      : " << "1.0" << endl;
    cout << endl;
    cout << "Help enabled : " << boolalpha << configuration_settings.is_help_enabled() << endl;
    cout << "Max Number of transitions to perform at a time : " << configuration_settings.get_maximum_number_of_transitions() << endl;
    cout << "Max number of cells displayed on tape head (Left & Right) : ";
    cout << configuration_settings.get_maximum_number_of_cells() << endl;

    cout << endl;
    cout << "Touring Machine Name : " << this->tm_name << endl;

    cout << "Status : ";
    if(!turing_machine.is_used())
        cout << "TM has not been run on an input string during-session" << endl;
    else if(turing_machine.is_operating())
        cout << "TM is currently running on an input string" << endl;
    else
        cout << "TM has completed operation on an input string during session" << endl;

    cout << "Last input String : " << turing_machine.input_string() << "\t";

    if(turing_machine.is_accepted_input_string() && !turing_machine.is_rejected_input_string())
        cout << "Accepted in ";
    else if(!turing_machine.is_accepted_input_string() && turing_machine.is_rejected_input_string())
        cout << "Rejected in ";
    else
        cout << "Not Accepted or Rejected in ";

    cout << turing_machine.total_number_of_transitions() << " Transitions" << endl;    
}

//ok
void User_Interface::HelpCommand()
{
    if (!configuration_settings.is_help_enabled())
    {
        configuration_settings.enable_help();
        cout << "Help Enabled!" << endl;
    }

    else
    {
        configuration_settings.disable_help();
        cout << "Help Disabled" << endl;
    }
}

void User_Interface::ExitCommand(string stringFile_path)
{
    if(write_to_string_file(stringFile_path))
        cout << "Input string file successfully written." << endl;
    else
        cout << "Unable to write to string file." << endl;

}

//ok
void User_Interface::ViewCommandDescription()
{
    cout << "Delete  " << "\t" << "D" << "\t" << "Delete input string from list" << endl;
    cout << "Exit    " << "\t" << "X" << "\t" << "Exit application" << endl;
    cout << "Help    " << "\t" << "H" << "\t" << "Help user with prompts or not" << endl;
    cout << "Insert  " << "\t" << "I" << "\t" << "Insert input string into list" << endl;
    cout << "List    " << "\t" << "L" << "\t" << "List input strings" << endl;
    cout << "Quit    " << "\t" << "Q" << "\t" << "Quit operation of Turing machine on input string" << endl;
    cout << "Run     " << "\t" << "R" << "\t" << "Run turing machine on input string" << endl;
    cout << "Set     " << "\t" << "E" << "\t" << "Set maximum number of transitions to perform" << endl;
    cout << "Show    " << "\t" << "W" << "\t" << "Show status of Application" << endl;
    cout << "Truncate" << "\t" << "T" << "\t" << "Truncate instantaneous description" << endl;
    cout << "View    " << "\t" << "V" << "\t" << "View turing machine" << endl;
}

//ok
bool User_Interface::is_valid_digit(string input)
{
    int index = 0;
    if (!input.empty())
    {
        while(index < (input.length())) 
        {
            if(isdigit(input[index]))
                ++index;
            else
                return false;
        }

        return true;
    }
    return false;
}


bool User_Interface::write_to_string_file(string stringFile_path)
{
    ofstream file;
    file.open(stringFile_path.c_str(), ios_base::out);
    bool flag = false;

    if (file.is_open())
    {
        for(int i = 0; i < input_string_list.size(); ++i) 
        {
            if(input_string_list.extract_string(i) == "")
                file << '\\' << endl;
            else
                file << input_string_list.extract_string(i) << endl;
        }
        flag = true;
    }
    else
    {
        flag = false;
    }
    return flag;
}

bool User_Interface::read_from_string_file(string stringFile_path)
{
    ifstream file;
    file.open(stringFile_path.c_str(), ios_base::in);
    string token;
    bool flag = true;

    if(file.is_open())
    {
        while(file >> token) 
        {
            if (token.size() == 1 && token[0] == '\\')
            {
                input_string_list.insert_string("");
            }
            else if(turing_machine.is_valid_input_string(token) && !input_string_list.is_string_in_list(token))
            {
                input_string_list.insert_string(token);
            }
            else 
            {
                cout << "Invalid string in input string file: " << token << endl;
                flag = false;
            }
        }
        return flag;
    }
    else
    {
        return false;
    }
}