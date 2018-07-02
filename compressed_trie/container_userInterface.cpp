#include "container.h"

//this function will read  and process the user input from the command line 
int container::read_user_input(string &inputPattern)
{
	string user_input;
	string token;
	string command;
	int inputCount = 0;
	getline(cin, user_input, '\n');
	istringstream iss(user_input);

	//parse line for individual words
	while(getline(iss, token, ' '))
	{
		token = convert_to_upper(token);
		if (token == "PREFIX" || token == "SUFFIX" || token == "EXIT") {

			command = token;
		}

		else {

			token = remove_nonAlphaNumberic(token);
			inputPattern = token;
		}
		inputCount++;
	}

	//return decision if there is valid command && correct amount of input
	if(command.empty() == false && inputCount == EXPECTED_INPUT) {
		if(command == "PREFIX")
			return PREFIX;
		else if(command == "SUFFIX")
			return SUFFIX;
	}

	else if(!command.empty() && inputCount == EXIT_EXPECTED_INPUT && command == "EXIT")
		return EXIT;

	return INVALID_INPUT;
}

//Description: This function will direct user input to a specific
// 	function specified by the user input.
void container::mainMenu()
{
	bool   terminate = false;
	int    user_decision = START;
	string searchPattern;
	int    status = START;

	//the while loop will end only when the user enters 'exit'
	//command.
	while (terminate == false)
	{
		user_decision = read_user_input(searchPattern);
		switch(user_decision)
		{
			case EXIT:
				terminate = true;
				break;

			case PREFIX:
				//PREFIX SEARCH HERE
				prefixSearch_Initialization(searchPattern);
				break;

			case SUFFIX:
				//SUFFIX SEARCH HERE
				suffixSearch_Initialization(searchPattern);
				break;
		}
	}
}