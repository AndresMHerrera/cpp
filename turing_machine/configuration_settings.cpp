#include "configuration_settings.h"

Configuration_Settings::Configuration_Settings()
{
    help_flag = false;
    maximum_number_of_transitions = 1;
    maximum_number_of_cells = 32;
}

void Configuration_Settings::disable_help()
{
    help_flag = false;
}

void Configuration_Settings::enable_help()
{
    help_flag = true;
}

bool Configuration_Settings::is_help_enabled()
{
    return help_flag;
}

int Configuration_Settings::get_maximum_number_of_cells()
{
    return maximum_number_of_cells;
}

int Configuration_Settings::get_maximum_number_of_transitions()
{
    return maximum_number_of_transitions;
}

void Configuration_Settings::set_maximum_number_of_cells(int input)
{
    maximum_number_of_cells = input;
}

void Configuration_Settings::set_maximum_number_of_transitions(int input)
{
    maximum_number_of_transitions = input;
}