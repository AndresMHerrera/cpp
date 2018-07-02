#include "container.h"

//not used
container::container(char const *argv[])
{
	create_map();
	process_file(argv);
}

//no dynamic memory allocated - not used
container::~container(){}


/***********************************************************************
//will insert new pattern into vector, pattern will include punction(original text)

***********************************************************************/
void container::vector_insertPattern(string pattern, int pageNumber, int lineNumber)
{
	//case: first pattern insertion, creates new page & line
	if(lookup.empty()) {
		lookup.push_back(pages());
		lookup[pageNumber].line.push_back(lines());
	}
		
	//case: not empty, minimum 1 page is in vector
	else {

		//determine if new page needs to be created
		if(pageNumber+1 > lookup.size()) // +1 since pages counted starting at zero
			lookup.push_back(pages());

		//determine if new line needs to be created.
		if(lineNumber+1 > lookup[pageNumber].line.size())
			lookup[pageNumber].line.push_back(lines());
	}

	//insert new pattern
	lookup[pageNumber].line[lineNumber].word.push_back(pattern);
}


/***********************************************************************
Will print the surrounding words of a specified pattern

***********************************************************************/
void container::print_surroundingPatter(int pageNumber, int lineNumber, int wordNumber)
{
	int march = wordNumber;
	int count = 0;
	int max_print = wordNumber+2;

	//print page and line number
	cout << "Page " << pageNumber+1 << ", " << "Line " << lineNumber << endl; //12.12

	//move 2 patterns to left(if possible)
	while(march >= 0 && count != 2) {

		//do not decrement march if zero, to avoid going out of bound
		if(march != 0) {
			march--;
			count++;
		}
		else
			break;
	}

	//at this point MARCH should be two patterns before main Pattern, print line
	cout << '\t' << "...";
	while(march <= max_print && march <= lookup[pageNumber].line[lineNumber].word.size() - 1) {

		cout << lookup[pageNumber].line[lineNumber].word[march];

		//decide wheter to print a space char or ellipsis
		if(march+1 <= max_print && march+1 <= lookup[pageNumber].line[lineNumber].word.size() - 1)
		 	cout << ' ';
		else
			cout << "..." << endl;

		march++;
	}
}

/***********************************************************************
//this function will read the txt file line by line and store it into a vector

***********************************************************************/
void container::process_file(char const *argv[])
{
	vector<string> lines;
	int line_count = 0;
	int page_count = 0;
	string input;
	ifstream file;

	file.open(argv[1], ios_base::in);

	//start reading if file opened successfully
	if(file.is_open()) {

		while(!file.eof()) {

			getline(file, input,'\n');

			if(file.eof()) {
				break;
			}

			//insert line into vector
			lines.push_back(input);
			line_count++;

			//process the page, clear lines vector,reset line_count, increment page_count
			if(line_count == MAX_LINES)	{
				process_page(lines,page_count);
				lines.clear();
				line_count = 0;
				page_count++;
			}
		}	

		file.close();

		//process remaining lines, as a new page
		if(!lines.empty())
			process_page(lines, page_count);
	}	
}


/***********************************************************************
//THIS FUNCTION WILL PROCESS A PAGE OF 20 LINES

***********************************************************************/
void container::process_page(vector<string> & lines,int page_count)
{
	int line_count = 0;

	for(int i = 0; i < lines.size(); i++){

		//insert if the line is not empty
		if(lines[i].size() != 0) {
			process_line(lines[i],page_count,line_count);
			line_count++;
		}
	}
}


/***********************************************************************
//This function will parse a line for individual words,
//Also, check if word is 1 of top 100 most common and ignore,
//Else, insert into trie.
***********************************************************************/
void container::process_line(string line, int page_number, int line_number)
{
	int word_count = 0;
	string token;
	istringstream iss(line);

	//parse line for individual words
	while(getline(iss, token, ' '))
	{
		//token contains individual word.
		//store TOKEN into vector, will be used to reference nearby
		//words.
		vector_insertPattern(token,page_number,line_number);

		token = convert_to_upper(token);
		token = remove_nonAlphaNumberic(token);
		token = trim_spaces_of_string(token);

		//determine if it is a common word.
		//IF NOT COMMON, INSERT INTO TRIE HERE
		if(map[token] != 1 && !token.empty()) {

			//will split word into suffixes and insert each suffix into trie
			suffixTree.wordSplit(token,page_number,line_number,word_count);
			prefixTree.insert_pattern(token,page_number,line_number,word_count,INITIAL_INDEX);
		}

		word_count++;
	}
}


/***********************************************************************
This function will remove any non alphanumeric chars
***********************************************************************/
string container::remove_nonAlphaNumberic(string token)
{
	string newString;

	for(int i = 0; i < token.size(); i++) {

		//remove punctionion and store into newString
		if(isupper(token[i]) || isdigit(token[i]))	//12.11
			newString.push_back(token[i]);
	}

	return newString;
}


/***********************************************************************
this function will convert a string into uppercase
***********************************************************************/
string container::convert_to_upper(string input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		if(islower(input[i]))
			input[i] = toupper(input[i]);
	}

	return input;
}

/***********************************************************************
this function will create a map that will be used to prevent the insertion
of common words
***********************************************************************/
void container::create_map()
{
	ifstream file;
	string user_input;

	file.open("commonWords.txt", ios_base::in);

	//start reading if file opened successfully
	if(file.is_open()) {

		while(!file.eof()) {

			getline(file, user_input, '\n');

			//prevents from re-reading the last line of the file
			if(file.eof()) {
				break;
			}

			user_input = trim_spaces_of_string(user_input);
			user_input = convert_to_upper(user_input);

			//insert into map
			map[user_input]++;
		}

		file.close();
	}
}

//This funtion will trim spaces from a string
string container::trim_spaces_of_string(string input)
{
	string modifiedString;
	int firstChar = 0;
	int lastChar = input.size()-1;//points to last char of input

	//find occurence of the first char of the string
	while(isspace(input[firstChar]))
		firstChar++;
	//at end of loop firstChar should be the index of the occurence of the first char in the input string

	//remove trailing spaces
	while(isspace(input[lastChar]))
		lastChar--;

	//create modified string(will not contain spaces)
	for (int i = firstChar; i <= lastChar; ++i)
	{
		modifiedString.push_back(input[i]);
	}

	return modifiedString;
}