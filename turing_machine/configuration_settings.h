#ifndef CONFIGURATION_SETTINGS_H
#define CONFIGURATION_SETTINGS_H

#include <iostream>
using namespace std;

class Configuration_Settings
{
private:
    bool help_flag;
    int maximum_number_of_cells;
    int maximum_number_of_transitions;

public:
    Configuration_Settings();
    void disable_help();
    void enable_help();
    bool is_help_enabled();
    int get_maximum_number_of_cells();
    int get_maximum_number_of_transitions();
    void set_maximum_number_of_cells(int input);
    void set_maximum_number_of_transitions(int input);
};


#endif
