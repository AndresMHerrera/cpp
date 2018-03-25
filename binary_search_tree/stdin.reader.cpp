#include "stdin.reader.h"

/****************************************************************
Description : The purpose of this function is to read the user 
			input from standard in, and determine if the user
			input should be processed or not. 

precondition : none

postcondition : All user input will be read, all valid input will
			be inserted into a binary search tree, and will stop
			reading when "END" statement in inputed. 
****************************************************************/
vector<int> STDinReaderService::read_stdin()
{
	string userInput;
	bool endReading_flag = NO_SUCCESS;
	vector<int> processedInput;

	//continue reading input until flag is set to true by one of the conditions
	while (endReading_flag == NO_SUCCESS)
	{

		cin >> userInput;

		//stop reading when the END_READING_INDICATOR is found in input
		if (userInput == END_READING_INDICATOR)
			endReading_flag = SUCCESS;

		else
		{

			// TODO: rework this logic

			//the purpose of the following conditions is to check for
			//invalid input of the form : "-0", "-009"

			//ensure that only a zero is inputed
			if (userInput[FIRST] == CASE_1 && userInput[SECOND] == CASE_2) {
				processedInput.push_back(process_input(userInput));
			}

			//ensures that a valid negative integer is inputed
			if (userInput[FIRST] == CASE_3 && userInput[SECOND] != CASE_1) {
				processedInput.push_back(process_input(userInput));
			}

			//ensures other valid integers
			if (userInput[FIRST] != CASE_1 && userInput[FIRST] != CASE_3) {
				processedInput.push_back(process_input(userInput));
			}
		}
	}

	return processedInput;
}

/************************************************************************
Description : This purpose of this function is to process the user input.
				That will include checking for valid user input, and 
				inserting the value into binary search tree. 

precondition : Will accept a pointer to characters.

postcondition : there is no return value, but the user input will have
					been inserted into binary search tree.
************************************************************************/
int STDinReaderService::process_input(string input)
{
	bool validInput_flag = SUCCESS;
	int march = 0;

	if (input[march] == CASE_3) //check if theres a negatie sign
		march++;

	//check if input is all digits
	while (march < input.size())
	{

		if (!isdigit(input[march]))
		{
			validInput_flag = NO_SUCCESS;
			break;
		}

		march++;
	}

	//convert to integer format, and insert final_copy if input was valid
	if (validInput_flag)
	{

		int finalCopy = atoi(input.c_str());
		return finalCopy;
		// TODO: return finalCopy value
		//insertStart(finalCopy); 	//CHANGE TO INSERT START
	}
}
