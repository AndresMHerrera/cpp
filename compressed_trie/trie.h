#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define FIRST_ELEMENT 0
#define INITIAL_INDEX 0
using namespace std;
struct treeNode;

struct print_object
{
	int page;
	int line;
	int word;
	print_object(int pageN, int lineN, int wordN) {
		page = pageN;
		line = lineN;
		word = wordN;
	}
};

struct listNode
{
	treeNode * child;
	listNode * next;
	listNode * prev;

	listNode(treeNode * child_i, listNode * next_i, listNode * prev_i) {
		child = child_i;
		next = next_i;
		prev = prev_i;
	}
};

struct terminalNode
{
	int pageNum;
	int lineNum;
	int wordNum;
	terminalNode * next;
	terminalNode * prev;
	terminalNode(int page, int line, int word, terminalNode * next_i, terminalNode * prev_i) {
		pageNum = page;
		lineNum = line;
		wordNum = word;
		next = next_i;
		prev = prev_i;
	}
};

struct treeNode
{
	string pattern;
	listNode * first_c;		//list of pointers to treeNodes
	terminalNode * first_t;	//list of terminalNodes

	treeNode(string pattern_i, listNode * child_ptr, terminalNode * terminal)
	{
		pattern = pattern_i;
		first_c = child_ptr;
		first_t = terminal;
	}
};


class trie
{
private:
	treeNode * rootNode;	//node should not contain data
	int previous_index;
public:
	trie();
	~trie();
	void destroy_tree(treeNode * temp);
	void destroy_child_list(treeNode * target);
	void destroy_terminal_list(treeNode * temp);
	bool determine_compatability_ofPatterns(treeNode * temp_ptr,string newString,int &index,int & compared_chars);
 	void Determine_chars_inCommon(string &oldString, string &newString, string &parentString, int index);

	bool search_for_matchingPattern(string newString, treeNode *& temp, listNode *& previous, int index);
	bool has_children(treeNode * target);
	void wordSplit(string input,int pageN, int lineN, int wordN);
	void insert_pattern(string newString, int pageN, int lineN, int wordN, int index);
	bool verify_pattern(string tempString, string newString, int index);
	bool getNext_position(string newString, int &index, listNode *& previous, treeNode *& temp, int & compared_chars);
 	bool has_matchingChar(string newString, treeNode * target);
	treeNode * create_newChild_treeNode(treeNode * target, string newString);
	void create_terminalNode(treeNode * temp,int pageN, int lineN, int wordN);
	void caseOne_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  		   string parentString, int pageN, int lineN, int wordN,int split_flag);
	void caseTwo_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  		   string parentString, int pageN, int lineN, int wordN,int split_flag);
	void caseThree_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  			 string parentString, int pageN, int lineN, int wordN,int split_flag);
	void caseFour_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  			string parentString, int pageN, int lineN, int wordN, int split_flag);

//suffix search
void retrieve_suffix_info(treeNode * temp,vector<print_object> & container);
void suffix_search(string pattern, treeNode * temp, vector<print_object> & container, int index);
vector<print_object> suffix_search_start(string inputPattern);
bool complete_patternComparison(string inputPattern, string temp,int & index);
void retrieve_info(treeNode * temp, vector<print_object> & container);


//vector duplicate removal
void remove_vectorDuplicates(vector<print_object> & container);
bool determine_ifDuplicate(vector<print_object> & copy, vector<print_object> & container,const int index);

//prefix
void prefix_search(string pattern, treeNode * temp, vector<print_object> & container, int index);
vector<print_object> prefix_search_start(string inputPattern);

};

#endif