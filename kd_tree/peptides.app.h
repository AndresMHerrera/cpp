// Merge sort algorithm source : Mark Allen Weiss "Data Structures and Algorithm Analysis in C++"

#ifndef CONTAINER_INCLUDED
#define CONTAINER_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cmath>
#include "hash_table.h"
#include "k_d_tree.h"
#include "file.reader.h"
#include "string.service.h"
using namespace std;

#define DATA_SIZE 2
struct c_node
{
	string	peptide;
	double * data; // data[0] == mass, data[1] == NET

	c_node(string peptide, double mass, double NET) {
		data = new double[DATA_SIZE];
		data[0] = mass;
		data[1] = NET;
		this->peptide = peptide;
	}

	~c_node() 
	{
		delete [] data;
	}		
};

class PeptidesApp
{
private:
    StringService stringService;
	FileReader fileReader;
	hash_table aminoAcidsHashTable;
	int size; // TODO: get rid of this and use a vector on peptideDatabase

	c_node ** peptideDatabase;
	kd_tree tree;

public:	
	PeptidesApp(char const * argv[]);
	~PeptidesApp();

	void insert(string peptide, double mass, double NET);
	void create_tree_start();
	void create_kd_tree(int index_i, int index_e, int level);	
	void assign_data(c_node **temp, int temp_index, int list_index);
	void mergeSort(int index_i, int index_e, int level);
	void mergeSort_divide(c_node ** temp, int index_i, int index_e, int level);
	void mergeSort_merge(c_node **temp, int leftPos, int rightPos, int rightEnd, int level);


	// New functions
	void initAminoAcidHashTable(string fileName);
	void initPeptideDatabase(string fileName);
	double calculatePeptideMass(string peptide);
	void printPeptideDatabase();
	void initNearestNeighborSearchForObservedList(string fileName);
};

#endif