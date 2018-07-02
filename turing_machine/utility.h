#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

static string trim_trailing_spaces_of_string(string input);
static string trim_leading_spaces_of_string(string input);
static string trim_leading_and_trailing_spaces_of_string(string input);
static string convert_to_upper(string input);
static bool is_keyword_format(string input);
static bool is_valid_keyword(string input, string validKeyword);
static bool is_valid_state_name_format(string input);
static bool is_valid_alphabet(string input);
static bool is_valid_direction(string input);

#endif
