#ifndef USER_INTERFACE_H // these are called included guards, prevent double declaration of identifier
#define USER_INTERFACE_H

#include <iostream>
#include <string>
#include "configuration_settings.h"
#include "input_string_list.h"
#include "turing_machine.h"
#include <cstdlib>
#include <sstream>
using namespace std;

class User_Interface
{
private:
    Configuration_Settings configuration_settings;
    Turing_Machine turing_machine;
    Input_String_List input_string_list;
    string tm_name;

public:
    User_Interface();
    ~User_Interface();

    bool loadFiles(string definitionFile_path, string stringFile_path, string TM_name);
    void programFlowControl(string stringFile_path);
    char CommandPrompt();
    void HelpCommand();
    void ShowCommand();
    void ViewCommand();
    void ListCommand();
    void InsertCommand();
    void DeleteCommand();
    void SetCommand();
    void TruncateCommand();
    void RunCommand();
    void QuitCommand();
    void ExitCommand(string stringFile_path);
    void ViewCommandDescription();


    bool is_valid_digit(string input);
    bool write_to_string_file(string stringFile_path);
    bool read_from_string_file(string stringFile_path);



};


#endif