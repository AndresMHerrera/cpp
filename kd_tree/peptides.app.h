// Merge sort algorithm source : Mark Allen Weiss "Data Structures and Algorithm Analysis in C++"

#ifndef PEPTIDES_APP_INCLUDED
#define PEPTIDES_APP_INCLUDED

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
#include "peptide.database.h"
using namespace std;

class PeptidesApp
{
private:
    StringService stringService;
	FileReader fileReader;
	hash_table aminoAcidsHashTable;
	PeptideDatabase peptideDatabase;
	kd_tree tree;

public:	
	PeptidesApp(char const * argv[]);
	~PeptidesApp();

	void create_tree_start();
	void create_kd_tree(int index_i, int index_e, int level);	

	void initAminoAcidHashTable(string fileName);
	void initPeptideDatabase(string fileName);
	void initNearestNeighborSearchForObservedList(string fileName);
	double calculatePeptideMass(string peptide);
	void printPeptideDatabase();
};

#endif