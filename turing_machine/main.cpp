/******************************************************
Author: Andres Herrera
Date: Month Day, Year
Course: Cpts Course Number
OS: Ubuntu 14.04 LTS
Compiler: GNU g++

Description: 
******************************************************/
#include "user_interface.h"


int main(int argc, char * argv[])
{
    User_Interface ui;
    string definitionFile_path;
    string stringFile_path;
    string tm_name;
    //names must match
    //argv[1] == tm definition file with no extension. string file will have same name with .str ext.
    //input file MUST NOT contain extension
    //user will provide full/relative path


    if (argv[1] != NULL && argc == 2)
    {
        definitionFile_path = argv[1];
        tm_name = definitionFile_path;
        stringFile_path = definitionFile_path + ".str";
        definitionFile_path += ".def";
        
        if(ui.loadFiles(definitionFile_path, stringFile_path, tm_name))
            ui.programFlowControl(stringFile_path);
        else
        {
            cout << "usage: $<executable> <turing machine definition file (exclude file extension)>" << endl;
        }
    }
    else
    {
        cout << "usage: $<executable> <turing machine definition file (exclude file extension)>" << endl;
    }

    return 0;
}