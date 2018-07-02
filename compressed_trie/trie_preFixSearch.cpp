#include "trie.h"
/*********************************************************************

*********************************************************************/
void trie::prefix_search(string pattern, treeNode * temp, vector<print_object> & container, int index)
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

*********************************************************************/
vector<print_object> trie::prefix_search_start(string inputPattern)
{
	vector<print_object> container;
	prefix_search(inputPattern,rootNode,container,INITIAL_INDEX);

	//REMOVE DUPLICATES HERE 
	remove_vectorDuplicates(container);

	return container;
}