#include "peptides.app.h"

/****************************************************************************
Description: The contructor will initialize private data members, in addition
			to construction the hash table, and determining the size of the
			peptide list.

****************************************************************************/
PeptidesApp::PeptidesApp(char const *argv[])
{
	this->initAminoAcidHashTable("aminoAcidList.csv");

	// REMOVE
	//this->aminoAcidsHashTable.printHashTable();

	this->initPeptideDatabase(string(argv[1]));

	// REMOVE
	//this->printPeptideDatabase();

	// TODO: work on improving this
	this->create_tree_start();

	// TODO: work on improving this
	this->initNearestNeighborSearchForObservedList(argv[2]);
}


PeptidesApp::~PeptidesApp(){}

/****************************************************************************
* Description: This function will process the specified file (aminoAcidList.csv)
* 				and initialize the aminoAcidsHashTable.
****************************************************************************/
void PeptidesApp::initAminoAcidHashTable(string fileName)
{
	vector<string> aminoAcidCommaSeparatedList = this->fileReader.readFileByLine(fileName);

	// Ignore the first line
	aminoAcidCommaSeparatedList.erase(aminoAcidCommaSeparatedList.begin());

	for (std::vector<string>::iterator it = aminoAcidCommaSeparatedList.begin(); it != aminoAcidCommaSeparatedList.end(); ++it)
	{
		stringstream stream((*it).c_str());

		while (stream.good())
		{
			string key;
			string value;
			double value_f;

			getline(stream, key, ',');
			getline(stream, value, '\n');

			value_f = atof(value.c_str());
			this->aminoAcidsHashTable.insert_hash_value(key[0], value_f);
		}
	}
}

/****************************************************************************
* Description: This function will process the specified file in (argv[1])
* 				to initialize the peptideDatabase.
****************************************************************************/
void PeptidesApp::initPeptideDatabase(string fileName)
{
	vector<string> peptideDatabaseFileLines = this->fileReader.readFileByLine(fileName);

	// Ignore the first line
	peptideDatabaseFileLines.erase(peptideDatabaseFileLines.begin());

	for (std::vector<string>::iterator it = peptideDatabaseFileLines.begin(); it != peptideDatabaseFileLines.end(); ++it)
	{
		stringstream stream((*it).c_str());

		while (stream.good())
		{
			string peptide;
			string NET_s;
			double NET_f;

			getline(stream, peptide, ',');
			getline(stream, NET_s, '\n');
			NET_f = atof(NET_s.c_str());

			//Insert into peptideDatabase
			this->peptideDatabase.insert(peptide, this->calculatePeptideMass(peptide), NET_f);
		}
	}
}

double PeptidesApp::calculatePeptideMass(string peptide)
{
	double mass = 0.0;
	for (int i = 0; i < peptide.size(); ++i)
	{
		mass += this->aminoAcidsHashTable.get_hash_value(peptide[i]); //returns mass
	}

	return mass;
}

/****************************************************************************
Description: This function will read a file for witch the nearest neigbor
			of each input must be calculated.

output : Will display the closest peptide corresponding to the input. 
		Information displayed on termimal,
		-Observed ID
		-Peptide
		-NET
		-Mass
		-Observed NET
		-Observed Mass
****************************************************************************/
void PeptidesApp::initNearestNeighborSearchForObservedList(string fileName)
{
	int ID_i;
	double mass_f;
	double NET_f;
	string ID_s;
	string mass;
	string NET_s;

	cout << "\nObserved ID, Peptide, NET, Mass, Observed NET, Observed Mass" << endl;

	vector<string> observedListFileLines = this->fileReader.readFileByLine(fileName);

	// Ignore the first line
	observedListFileLines.erase(observedListFileLines.begin());

	for (std::vector<string>::iterator it = observedListFileLines.begin(); it != observedListFileLines.end(); ++it)
	{
		stringstream stream((*it).c_str());

		while (stream.good())
		{
			getline(stream, ID_s, ',');
			getline(stream, NET_s, ',');
			getline(stream, mass, '\n');

			NET_f = atof(NET_s.c_str());
			mass_f = atof(mass.c_str());
			ID_i = atoi(ID_s.c_str());

			//search for nearest neighbor
			tree.start_nearest_neighbor_search(ID_i, mass_f, NET_f);
		}
	}

	cout << endl;
}

/****************************************************************************
Description: This function will calculate the median index of an array,
			given the starting position of the array, and the ending
			position of the array.
output : Will return the median given two indeces.
****************************************************************************/
int calculate_median(int start, int end)
{
	if (start == end)
		return start;

	else
	{
		int median = ceil(((end - start) / 2.0));
		if (median == 1)
			return start;
		else
		{
			median = median + start;
			return median;
		}
	}
}

/****************************************************************************
Description: This function will initialize necessary values to begin the 
			construction of the kd tree.
output: none
****************************************************************************/
void PeptidesApp::create_tree_start()
{
	int level = 0;   //sorts according to level, 0 == mass, 1 == NET
	int index_i = 0; //index of first element in the list
	int index_e = this->peptideDatabase.size() - 1; //index of last element in the list

	//will recursively create kd_tree
	create_kd_tree(index_i, index_e, level);

	//set tree visited to false
	tree.reset();
}

/****************************************************************************
Description: This function will recursively calculate the median of the peptide
			list, and insert the median into the kd_tree.

output: none
****************************************************************************/
void PeptidesApp::create_kd_tree(int index_i, int index_e, int level)
{
	if (index_e >= index_i)
	{
		//sort (axis aligned)
		this->peptideDatabase.sort(index_i, index_e, level);

		//find MID
		int median = 0;
		median = calculate_median(index_i, index_e);

		//insert MID into kd tree
		tree.insert(this->peptideDatabase.get(median).peptide, this->peptideDatabase.get(median).data[MASS_INDEX], this->peptideDatabase.get(median).data[NET_INDEX]);

		create_kd_tree(index_i, median - 1, 1 - level); // Left subarray
		create_kd_tree(median + 1, index_e, 1 - level); // Right subarray
	}
}

void PeptidesApp::printPeptideDatabase()
{
	for (int i = 0; i < this->peptideDatabase.size(); ++i)
	{
		cout << "Peptide:" << this->peptideDatabase.get(i).peptide << ", Mass:";
		cout << this->peptideDatabase.get(i).data[0];
		cout << ", NET:" << this->peptideDatabase.get(i).data[1] << endl;
	}
}