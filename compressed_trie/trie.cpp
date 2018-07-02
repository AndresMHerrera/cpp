#include "trie.h"


/*********************************************************************
Constructor will initialize private members
*********************************************************************/
trie::trie()
{
	rootNode = new treeNode("---", NULL,NULL);
	create_terminalNode(rootNode,-1,-1,-1);	
	previous_index = 0;
}

/*********************************************************************
this function will call destroy_tree
*********************************************************************/
trie::~trie()
{
	//will destroy the tree recursively
	destroy_tree(rootNode);

}

/*********************************************************************
this function will destroy the trie recursively
*********************************************************************/
void trie::destroy_tree(treeNode * temp)
{
	while(temp->first_c != NULL) {

		if(temp->first_c->child != NULL)
			destroy_tree(temp->first_c->child);

		if(temp->first_c->next != NULL)
			temp->first_c = temp->first_c->next;

		//at this point all subtrees under temp have been delted
		else {
			if(temp->first_c != NULL)
				destroy_child_list(temp);
			if(temp->first_t != NULL)
				destroy_terminal_list(temp);
		}
	}

	if(temp->first_t != NULL)
		destroy_terminal_list(temp);

	delete temp;
	temp = NULL;
}

/*********************************************************************
this function will destroy the list of pointers to trie nodes

*********************************************************************/
void trie::destroy_child_list(treeNode * target)
{
	//first_c should be pointing to last element of the child list,
	//Delete list in reverse order
	listNode * march = target->first_c;

	while(march != NULL) {

		target->first_c = target->first_c->prev;
		delete march;
		march = target->first_c;
	}
}

/*********************************************************************
this function will destory the list of terminal nodes
*********************************************************************/
void trie::destroy_terminal_list(treeNode * target)
{
	terminalNode * march = target->first_t;

	while(march != NULL) {
		target->first_t = march->next;
		delete march;
		march = target->first_t;
	}
}


/*********************************************************************
this function will return TRUE if it has children, false otherwise

*********************************************************************/
bool trie::has_children(treeNode * target)
{
	if(target->first_c != NULL)
		return true;
	else
		return false;
}	

/*********************************************************************
this function will split each word to retrieve the suffix used for 
suffix trie
*********************************************************************/
void trie::wordSplit(string input,int pageN, int lineN, int wordN)
{
	int march = -1;
	string temp;

	for (int i = input.size() -1; i >= 0; --i) {
		march = i;
		while(march <= input.size() - 1) {
			temp.push_back(input[march]);
			march++;
		}

		//INSERT HERE
		insert_pattern(temp,pageN,lineN,wordN,INITIAL_INDEX);
		temp.clear();
	}
}

/*********************************************************************
this function will insert a pattern the trie
*********************************************************************/
void trie::insert_pattern(string newString, int pageN, int lineN, int wordN, int index)
{
	treeNode * temp = rootNode;
	listNode * previous = NULL;
	treeNode * march = NULL;
	bool split_flag = false;
	bool loop_flag = true;
	int compared_chars = 0;

	if(has_children(temp) == false || has_matchingChar(newString,temp) == false) {
		create_terminalNode(create_newChild_treeNode(temp,newString),pageN,lineN,wordN);
	}

	else {

		//search for insertion locaton
		while(loop_flag == true) {

			//index,previous, and temp are modified inside -> when out of loop they are ready for insertion
			loop_flag = getNext_position(newString,index,previous,temp,compared_chars);
			compared_chars = 0;
		}

		//returns TRUE if complete temp->string pattern exist in newString(NO SPLIT),
		//FALSE otherwise(YES split)
		split_flag = verify_pattern(temp->pattern,newString,index);

		// This function will determine the chars in common btwn old & new until they differ, 
		// Then will store them in Parent.(will modify input strings for insertion)
		string oldString = temp->pattern;
		string parentString; 
		Determine_chars_inCommon(oldString,newString,parentString,index);

		//determine case of insertion
		if(oldString[FIRST_ELEMENT] == '\0' && newString[FIRST_ELEMENT] != '\0')
			caseOne_insertion(temp,previous,oldString,newString,parentString,pageN,lineN,wordN,split_flag);

		if(newString[FIRST_ELEMENT] == '\0' && oldString[FIRST_ELEMENT] != '\0')
			caseTwo_insertion(temp,previous,oldString,newString,parentString,pageN,lineN,wordN,split_flag);

		if(newString[FIRST_ELEMENT] == '\0' && oldString[FIRST_ELEMENT] == '\0')
			caseThree_insertion(temp,previous,oldString,newString,parentString,pageN,lineN,wordN,split_flag);

		if(newString[FIRST_ELEMENT] != '\0' && oldString[FIRST_ELEMENT] != '\0')
			caseFour_insertion(temp,previous,oldString,newString,parentString,pageN,lineN,wordN,split_flag);
	}

	//reset previous index
	previous_index = 0;
}

/*********************************************************************
this function will be used to check if a new parent node needs to 
be created.
*********************************************************************/
//if tempString exists in newString ->> RETURN FALSE -- NO SPLIT
//tempString DOES NOT exist in newString ->> RETURN TRUE -- YES SPLIT
//GIVEN TWO STRING IDENTIFY IF A SPLIT IS NEEDED
bool trie::verify_pattern(string tempString, string newString, int index)
{
	//assume there is always at least 1 char to compate
	string temp = tempString;
	int march = 0;

	//COMPARE AS LONG AS newString or tempString DOES NOT go out of bounds
	while(march <= temp.size()-1 && index <= newString.size()-1) {

		//if char match
		if(temp[march] == newString[index]) {
			index++;
			march++;
		}

		//else, dont match, YES SPLIT NEEDED
		else
			return true;
	}

	//return TRUE if not all chars from temp were compared against newString(meaning SPLIT NEEDED)
	if(march < temp.size()-1)
		return true;
	else if(march == temp.size()-1)		//ADDED TO FIX 12/8****
		return true;	
	else
		return false;
}

/*********************************************************************
This function will separate all chars in common between two string
and store them in variables, used when creating a new node.
*********************************************************************/
void trie::Determine_chars_inCommon(string &oldString, string &newString, string &parentString, int index)
 {
 	int march = 0;

	//when newString or tempString go out of bound
	while(march <= oldString.size()-1 && index <= newString.size()-1) {

		//if char match
		if(oldString[march] == newString[index]) {
			//insert matching char into parent string
			parentString.push_back(oldString[march]);
			index++;
			march++;
		}

		//current char doesnt match
		else
			break;
	}
	//at the end of loop, both indexes will point to character not matching

	//set newString
	if(index > newString.size()-1) { //no more chars to compare
		newString.clear();
		newString.push_back('\0');
	}
	else {
		string tempNew;
		while(index <= newString.size()-1) { //copy remaining non-matching chars
			tempNew.push_back(newString[index]);
			index++;
		}
		newString = tempNew;
	}

	//set oldString
	if(march > oldString.size()-1) {
		oldString.clear();
		oldString.push_back('\0');
	}

	else{
		string tempOld;
		while(march <= oldString.size()-1) { //copy remaining non matching chars
			tempOld.push_back(oldString[march]);
			march++;
		}
		oldString = tempOld;
	}
 }



/*********************************************************************
//this function will traverse the children of target pointer, it will compare
//the 1st char of each child pattern against the newString[index].
//modifies TEMP POINTER TO NEXT POSITION
//WILL SET THE PREVIOUS POINTER, AND TEMP, AND INDEX
//return false if no other position available, or temp->pattern does not 
//exist in newstrig pattern
*********************************************************************/
bool trie::getNext_position(string newString, int &index, listNode *& previous, treeNode *& temp, int & compared_chars)
{
	bool result1 = false;
	bool result2 = false;

	//continue if there is more treeNode && there is more chars to compare
	//TO CONTINUE LOOPING RESULT 1 AND 2 == TRUE
	if(temp->first_c != NULL && newString.size()-1 >= index) {

		//will search for next location and modify the temp to point there
		result1 = search_for_matchingPattern(newString,temp,previous,index);
		if(result1 == true)
			result2 = determine_compatability_ofPatterns(temp,newString,index,compared_chars);

		else{
			result2 = false;	//ADDED 12/6 fix index prob
		}
	}

	//RETURN TRUE WHEN LOCATION FOUND

	if(result1 == true && result2 == true)
		return true;

	//when false return the previous index
	else{
		index = index - previous_index;		//added to fix index problem
		return false;
	}
}

/*********************************************************************
//This function will determine if temps string pattern completely exists in the newstring
//starting in the given index.
//if the pattern completely exists, will return TRUE, and will modify "COMPARED CHARS" && index
//returns FALSE if pattern doesnt completely exists, DOES NOT MODIFY COMPARED CHARS

*********************************************************************/
bool trie::determine_compatability_ofPatterns(treeNode * temp_ptr,string newString,int &index,int & compared_chars)
{
	//assume there is always at least 1 char to compate
	string temp = temp_ptr->pattern;
	int march = 0;

	//when to stop comparing
	//when newString has less chars to compare
	if(((newString.size()-1) - index) < (temp.size()-1)) {

		previous_index = compared_chars;
		return false;
	}

	//when newString or tempString go out of bound
	while(march <= temp.size()-1 && index <= newString.size()-1) {

		if(temp[march] == newString[index]) {
			index++;
			march++;
			compared_chars++;
		}

		//else, dont match
		else {
			previous_index = compared_chars;		
			compared_chars = 0;
			return false;
		}
	}

	previous_index = compared_chars;
	return true;
}


/*********************************************************************
//this function will traverse the children of target pointer, it will compare
//the 1st char of each child pattern against the newString. **USES 0 INDEX FOR TEMP STRING
//returns TRUE if a new position was found. modifies temp to point to it
//WILL ALSO SET THE PREVIOUS POINTER if a position is found
*********************************************************************/
bool trie::search_for_matchingPattern(string newString, treeNode *& temp, listNode *& previous, int index)
{
	listNode * march = temp->first_c;

	//traverse childs comparing 1st char against the newString
	while (march != NULL && march->child->pattern[FIRST_ELEMENT] != newString[index]) {
		march = march->next;
	}

	//march will only be null if it fails to match a character(NO MATCHING PATTERN)
	if(march == NULL)
		return false;
	else {
		previous = march;		
		temp = march->child;
		return true;
	}
}

/*********************************************************************
//this function will traverse the children of target pointer, it will compare
//the 1st char of each child pattern against the newString.
//if a match is found will return true, otherwise false

*********************************************************************/
 bool trie::has_matchingChar(string newString, treeNode * target)
{
	listNode * march = target->first_c;

	//traverse childs comparing 1st char against the newString
	while (march != NULL && march->child->pattern[FIRST_ELEMENT] != newString[FIRST_ELEMENT]) {
		march = march->next;
	}

	//march will only be null if it fails to match a character
	if(march == NULL)
		return false;
	else
		return true;
}

/*********************************************************************
//This function will create a new listNode in "target" node, and
//create a new TreeNode
//returns pointer to new TreeNode created

*********************************************************************/
treeNode * trie::create_newChild_treeNode(treeNode * target, string newString)
{
	// used to store location of node where new TreeNode will be created
	listNode * newTarget = NULL; 

	//if child list is empty (1st insertion)
	if(target->first_c == NULL) {
		target->first_c = new listNode(NULL,NULL,NULL);
		newTarget = target->first_c;
	}

	//traverse child list to insert to listNode
	else {
		listNode * march = target->first_c;

		//search for insertion place; at end of loop march should be 1 node 
		//before insertion place.
		while(march->next != NULL) {
			march = march->next;
		}

		//create and initialize a new listnode
		march->next = new listNode(NULL,NULL,march);
		newTarget = march->next;
	}

	//create treeNode -> insert newString; at this point newTarget pointer
	//should point at newly created ListNode -> create treeNode
	newTarget->child = new treeNode(newString,NULL,NULL);

	return newTarget->child;	//return new treenode created

}

/*********************************************************************
//create Terminal node(page #, line #, word#)
//This function will create a terminal node in specified "target" node,
//and insert page#,line#,word#

*********************************************************************/
void trie::create_terminalNode(treeNode * temp,int pageN, int lineN, int wordN)
{
	//first insertion of terminal node
	if(temp->first_t == NULL) {
		temp->first_t = new terminalNode(pageN,lineN,wordN,NULL,NULL);
	}
	//traverse list to insert, insert at end of list
	else {
		terminalNode * march = temp->first_t;

		//go to end of list
		while(march->next != NULL) {
			march = march->next;
		}
		march->next = new terminalNode(pageN,lineN,wordN,NULL,march);
	}
}


/*********************************************************************
//	create newChild → store newString → create terminal node(P#,L#,W#)
//	temp → point to newChild
*********************************************************************/
void trie::caseOne_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  string parentString, int pageN, int lineN, int wordN, int split_flag)
{
	//NO SPLIT
	if (split_flag == false)
	{
		//	create newChild → store newString → create terminal node(P#,L#,W#)
		//	temp will → point to newChild
		treeNode * newChild = create_newChild_treeNode(temp,newString);
		create_terminalNode(newChild,pageN,lineN,wordN);
	}
}

/*********************************************************************
//SPLIT NEEDED
//	create a newParent → store parentString → create Terminal Node(P#,L#,W#)
// 	replace temp->string w/ oldString
// 	newParent → point to temp
// 	(prev ptr) child_ptr → point to newParent

*********************************************************************/
void trie::caseTwo_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  string parentString, int pageN, int lineN, int wordN,int split_flag)

{
	if(split_flag == true) {

		//	create a newParent → store parentString → create Terminal Node(P#,L#,W#)
		//	newParent → point to temp
		listNode * newParentListNode = new listNode(temp, NULL, NULL);	//1st listnode
		treeNode * newParent = new treeNode(parentString,newParentListNode,NULL);
		create_terminalNode(newParent,pageN,lineN,wordN);

		// 	replace temp->string w/ oldString
		temp->pattern = oldString;

		// 	(prev ptr) child_ptr → point to newParent
		previous->child = newParent;
	}

}

/*********************************************************************
//if newString & oldString == '\0'
//NO SPLIT
//	create Terminal node(page#, line#, word#)

*********************************************************************/
void trie::caseThree_insertion(treeNode * temp,listNode * previous, string oldString, string newString,
				  string parentString, int pageN, int lineN, int wordN,int split_flag)
{
	//no split needed
	if(split_flag == false) {

		//create Terminal node(page#, line#, word#)
		create_terminalNode(temp,pageN,lineN,wordN);

	}
}


/*********************************************************************
//SPLIT NEEDED
//	create a newParent → store parentString
//	replace temp->string w/ oldString
//	create newChild → store newString → add terminal node(pg# etc)
//	newParent → point to temp & newString
//	(prev ptr) child_ptr → point to newParent

*********************************************************************/
void trie::caseFour_insertion(treeNode * temp,listNode * previous,string oldString, string newString,
				  string parentString, int pageN, int lineN, int wordN,int split_flag)
{
	if(split_flag == true) {
		
		//	create a newParent → store parentString -> points to temp
		listNode * newParentListNode = new listNode(temp, NULL, NULL);	//1st listnode
		treeNode * newParent = new treeNode(parentString,newParentListNode,NULL);

		//	replace temp->string w/ oldString
		temp->pattern = oldString;

		//	create newChild → store newString → add terminal node(pg# etc)
		//	newParent → point to newChild		
		treeNode * newChild = create_newChild_treeNode(newParent, newString);
		create_terminalNode(newChild,pageN,lineN,wordN);

		//	(prev ptr) child_ptr → point to newParent
		previous->child = newParent;
	}
}

/*********************************************************************
This fuction will retrieve the info from a terminal node
*********************************************************************/
void trie::retrieve_suffix_info(treeNode * temp,vector<print_object> & container)
{
	terminalNode * march = temp->first_t;

	while(march != NULL) {
		container.push_back(print_object(march->pageNum,march->lineNum,march->wordNum));
		march = march->next;
	}
}

/*********************************************************************
This fuction will traverse the terminal nodes and call retrieve_suffix_info

*********************************************************************/
void trie::retrieve_info(treeNode * temp, vector<print_object> & container)
{
	listNode * child_ptr = temp->first_c;

	//use depth first approach
	while(child_ptr != NULL) {

		retrieve_info(child_ptr->child,container);
		child_ptr = child_ptr->next;
	}

	//store node info into vector	
	if(temp->first_t != NULL)
		retrieve_suffix_info(temp,container);

}

/*********************************************************************
This fuction will exahust the input pattern and then traverse its 
subtree where pattern was exhausted.

*********************************************************************/
bool trie::complete_patternComparison(string inputPattern, string temp,int & index)
{
	int march = 0;
	//if the chars dont match pattern CANNOT exist - return false
	//breaks when newString or tempString go out of bound
	while(march <= temp.size()-1 && index <= inputPattern.size()-1) {

		//if char match
		if(temp[march] == inputPattern[index]) {

			index++;
			march++;
		}

		//else, dont match
		else
			return false;
	}

	//sequencial chars match
	return true;
}

/*********************************************************************
//this function will be the driver of the suffix search

*********************************************************************/
void trie::suffix_search(string pattern, treeNode * temp, vector<print_object> & container, int index)
{
	//exahust the pattern
	listNode * march = temp->first_c;
	bool result = true;			
	
	while(index <= pattern.size() -1 && march != NULL && result) {

		//compare 1st char of child
		if (march->child->pattern[FIRST_ELEMENT] == pattern[index]) {
			temp = march->child;
			march = temp->first_c;

			//should always return true unless sequencial chars do not match
			result = complete_patternComparison(pattern,temp->pattern,index);
		}

		else {
			march = march->next;
		}
	}
	//at the end of loop temp should point to the node that exausted the input pattern. Retrieve
	//subtree info from that point.

	//retrieve info if result ==true && pattern was exausted modified 12/7
	if(result && index > pattern.size() -1)	
		retrieve_info(temp, container);
	else
		cout << "pattern does not exist" << endl;

}

/*********************************************************************
//this function will start the search for the inputed pattern

*********************************************************************/
vector<print_object> trie::suffix_search_start(string inputPattern)
{
	vector<print_object> container;
	suffix_search(inputPattern,rootNode,container,INITIAL_INDEX);
	remove_vectorDuplicates(container);

	//REORDER VECTOR PRINT OBJECTS HERE 12.11
	
	return container;
}

/*********************************************************************
//this function will remove all duplicates from container vector

*********************************************************************/
void trie::remove_vectorDuplicates(vector<print_object> & container)
{
	vector<print_object> copy;
	bool result = false;

	for (int i = 0; i < container.size(); ++i)
	{
		if (copy.empty())	//1st element inserted
			copy.push_back(container[i]);

		else { //determine if element is a duplicate

			//returns false if it is not a duplicate
			result = determine_ifDuplicate(copy,container,i);

 			//insert if not a duplicate
			if(result == false)
				copy.push_back(container[i]);
		}
	}

	//at end of loop all non duplicates will be in copy vector
	//move copy vector contents to container vector
	container.clear();
	for (int i = 0; i < copy.size(); ++i)
	{
		container.push_back(copy[i]);
	}
}

/*********************************************************************
//will traverse copy vector in search for a duplicate element from 
container vector(specified by index) returns true if duplicate is found
//returns false if duplicate is not found

*********************************************************************/
bool trie::determine_ifDuplicate(vector<print_object> & copy, vector<print_object> & container,const int index)
{
	for (int i = 0; i < copy.size(); ++i) {

		//return true if its a duplicate
		if(copy[i].page == container[index].page && copy[i].line == container[index].line
		   && copy[i].word == container[index].word)
		{
			return true;
		}
	}

	return false;	//no duplicate exists

}
