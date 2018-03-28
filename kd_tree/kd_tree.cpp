#include "k_d_tree.h"

/****************************************************************************
Description: Constructor will initialize private data members

****************************************************************************/
kd_tree::kd_tree()
{
	root = NULL;
	current_best = NULL;
	best_distance = INITIAL_VALUE;
	dimensions = TOTAL_DIMENSIONS;
}

/****************************************************************************
Description: Destructor will call destroy_tree();


****************************************************************************/
kd_tree::~kd_tree()
{
	destroy_tree(root);
}

/****************************************************************************
Description: This function will destroy the tree recursively.
output: none.
****************************************************************************/
void kd_tree::destroy_tree(kd_node * temp)
{
	//destroy the tree until the root is set to NULL
	if (temp != NULL){
		destroy_tree(temp->left);
		destroy_tree(temp->right);
		delete temp;
		temp = NULL;

	}
}

/****************************************************************************
Description: This function will allocate memory for a new node, send the node
			to insert_node(); to be inserted.
output: none.
****************************************************************************/
void kd_tree::insert(string peptide, double mass, double NET)
{	
	kd_node * newNode = create_kd_node(peptide,mass,NET);
	int level = 0;
	insert_node(root, newNode, level);
}

/****************************************************************************
Description: This function will create a new kd_node.

output: Will return a pointer to the new kd_node.
****************************************************************************/
kd_node * kd_tree::create_kd_node(string peptide, double mass, double NET)
{
	kd_node * newNode = new kd_node(NULL,NULL, mass, NET, peptide, dimensions);
	return newNode;
}

/****************************************************************************
Description: This function will recursively traverse the tree to find the 
			insertion location of the node, and will insert it.
output: none
****************************************************************************/
void kd_tree::insert_node(kd_node * temp, kd_node * newNode, int level)
{
	if(root == NULL)
		root = newNode;

	// will compare MASS if level == 0,		x-axis
	// will compare NET if level == 1,		y-axis
	else if(newNode->data[level] < temp->data[level]) {
		if (temp->left == NULL)
			temp->left = newNode;
		else
			insert_node(temp->left,newNode, 1-level);
	}

	else {
		if(temp->right == NULL)
			temp->right = newNode;
		else
			insert_node(temp->right, newNode, 1-level);
	}
}

/****************************************************************************
Description: This function will calculate the distance between two points, 
using the distance formula.

output: Will return the distace. 
****************************************************************************/
double kd_tree::calculate_distance(kd_node * query_point, kd_node * next_best)
{
	if(query_point != NULL && next_best != NULL) {

		double temp1 = pow((next_best->data[0] - query_point->data[0]), 2);
		double temp2 = pow((next_best->data[1] - query_point->data[1]), 2);

		return sqrt((temp1 + temp2));
	}
}

/****************************************************************************
Description: This function will find the closest point given a input search
			point.
output : Will display the closest peptide corresponding to the input. 
		Information displayed on termimal,
		-Observed ID
		-Peptide
		-NET
		-Mass
		-Observed NET
		-Observed Mass
****************************************************************************/
void kd_tree::start_nearest_neighbor_search(int ID, double mass, double NET)
{
	int level = 0;
	kd_node * query_point = new kd_node(NULL,NULL,mass,NET,"--",2);
	find_nearest_neighbor(root,query_point,level);

	//cout << "Observed ID, Peptide, NET, Mass, Observed NET, Observed Mass" <<endl;
	cout << ID << ", " << current_best->peptide << ", " << current_best->data[1] << ", ";
	cout << current_best->data[0] << ", " << NET << ", " << mass << endl;

	delete query_point;

	//reset current_best
	current_best = NULL;
	reset();

}

/****************************************************************************
Description: This function will set the new current best point and distance,
			if applicable.
output: none.
****************************************************************************/
void kd_tree::set_best_distance(double newDistance, kd_node * next_best)
{
	//first time being set
	if(current_best == NULL) {
		best_distance = newDistance;
		current_best = next_best;
	}

	else if(newDistance < best_distance) {
		best_distance = newDistance;
		current_best = next_best;
	}
}

/****************************************************************************
Description: This function will traverse the the kd tree recursively to
			find the closest point to the given input point. 

output: none, Current_best pointer will be set to the closest point found.
****************************************************************************/
void kd_tree::find_nearest_neighbor(kd_node * temp, kd_node * query_point, int level)
{
	double newDistance = calculate_distance(query_point, temp);
	set_best_distance(newDistance,temp);

	//mark visited
	temp->visited = true;

	//go towards query_point
	//this section will check along where query_point would have been inserted
	if(query_point->data[level] < temp->data[level]) {
		if(temp->left != NULL && temp->left->visited == false)
			find_nearest_neighbor(temp->left,query_point,1-level);
	}

	else {	
		if(temp->right != NULL && temp->right->visited == false)
			find_nearest_neighbor(temp->right,query_point,1-level);
	}

	//do I need to search the left halfspace?
	if(temp->left != NULL && temp->left->visited == false &&
	 best_distance >= OneD_distance(temp,query_point,level)) 
	{
			find_nearest_neighbor(temp->left,query_point,1 - level);
	}

	//do I need to search the right halfspace?
	if(temp->right != NULL && temp->right->visited == false && 
		best_distance >= OneD_distance(temp, query_point,level))
	{
		find_nearest_neighbor(temp->right,query_point,1 - level);
	}
}

/****************************************************************************
Description: This function will calculate the one dimensional distace between
			two points(axis aligned).
output: will return a distance.
****************************************************************************/
double kd_tree::OneD_distance(kd_node * node_ptr, kd_node * query_point, int level)
{
	double OneD_distance = abs(node_ptr->data[level] - query_point->data[level]);

	return OneD_distance;
}

/****************************************************************************
Description: This function will initialize the reset_visited() function.

****************************************************************************/
void kd_tree::reset()
{
	reset_visited(root);
}

/****************************************************************************
Description: This function will recursively set the "visited" marker to false.

output: none.
****************************************************************************/
void kd_tree::reset_visited(kd_node * current_ptr)
{
	if (current_ptr != NULL) {
		current_ptr->visited = false;
		this->reset_visited(current_ptr->left);
		this->reset_visited(current_ptr->right);
	}
}	