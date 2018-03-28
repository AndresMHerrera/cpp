// Student : Herrera, Andres
// Course  : CPTS 223
// Homework: #4

#ifndef KD_TREE_INCLUDED
#define KD_TREE_INCLUDED

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#define TOTAL_DIMENSIONS 2
#define INITIAL_VALUE 0.0
using namespace std;

struct kd_node
{
	string peptide;
	bool visited;	// used when searching for nearest neighbor
	double * data;	// x-axis [0] == mass , y-axis [1] == NET	
	kd_node * left;
	kd_node * right;

	kd_node(kd_node * left, kd_node * right, double mass, double NET,string peptide, int dimensions) {
		data = new double[dimensions];
		data[0] = mass;
		data[1] = NET;
		this->peptide = peptide;
		this->left = left;
		this->right = right;
	}

	~kd_node() {
		delete [] data;
	}	
};

class kd_tree
{
private:
	kd_node * root;
	int dimensions;
	kd_node * current_best;
	double best_distance;

public:
	kd_tree();
	~kd_tree();
	void destroy_tree(kd_node * temp);
	kd_node * create_kd_node(string peptide, double mass, double NET);
	void insert(string peptide, double mass, double NET);	
	void insert_node(kd_node * temp, kd_node * newNode, int level);
	double calculate_distance(kd_node * query_point, kd_node * next_best);
	void read_observed_list(); 
	void start_nearest_neighbor_search(int ID, double mass, double NET);
	void find_nearest_neighbor(kd_node * temp, kd_node * query_point, int level);
	void set_best_distance(double newDistance, kd_node * next_best);
	void check_subtrees(kd_node * temp, kd_node * query_point, int level);
	void reset();
	void reset_visited(kd_node * current_ptr);
	double OneD_distance(kd_node * node_ptr, kd_node * query_point,int level);
};


#endif