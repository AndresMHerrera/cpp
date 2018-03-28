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
	// this->read_observed_file(argv);
	this->initNearestNeighborSearchForObservedList(argv[2]);
}


/****************************************************************************
* Description: This function will free all memory allocated during runtime
****************************************************************************/
PeptidesApp::~PeptidesApp()
{
	//deleting nodes
	for (int i = 0; i < size; ++i)
	{

		if (this->peptideDatabase[i] != NULL)
			delete this->peptideDatabase[i];
	}

	//DELETE ARRAY
	delete[] this->peptideDatabase;
}

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

	this->size = peptideDatabaseFileLines.size();

	// TODO: work on replacing by using a vector
	this->peptideDatabase = new c_node *[this->size];

	for (int i = 0; i < this->size; ++i)
	{
		this->peptideDatabase[i] = NULL;
	}
	// END //////

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
			this->insert(peptide, this->calculatePeptideMass(peptide), NET_f);
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
Description: This function will insert a new peptide in the next available 
			location of the peptide list.
output : none
****************************************************************************/
void PeptidesApp::insert(string peptide, double mass, double NET)
{
	int index = 0;

	while (this->peptideDatabase[index] != NULL)
	{

		index++;
	} //at end of loop, index, should be in a empty location

	//insert new data
	this->peptideDatabase[index] = new c_node(peptide, mass, NET);
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
	int level = 0;			//sorts according to level, 0 == mass, 1 == NET
	int index_i = 0;		//index of first element in the list
	int index_e = size - 1; //index of last element in the list

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
		mergeSort(index_i, index_e, level);

		//find MID
		int median = 0;
		median = calculate_median(index_i, index_e);

		//insert MID into kd tree
		tree.insert(this->peptideDatabase[median]->peptide, this->peptideDatabase[median]->data[0], this->peptideDatabase[median]->data[1]);

		create_kd_tree(index_i, median - 1, 1 - level); // Left subarray
		create_kd_tree(median + 1, index_e, 1 - level); // Right subarray
	}
}

/****************************************************************************
Description: This function will serve as the driver for the sorting process.
			It will allocate memory for temporary storage, begin the sorting
			process, and free memory allocated. 
output: none.			
****************************************************************************/
void PeptidesApp::mergeSort(int index_i, int index_e, int level)
{
	//create temp array
	int newSize = (index_e - index_i) + 1;
	c_node **temp = new c_node *[newSize];

	//initialize temp, allocates memmroy
	for (int i = 0; i < newSize; ++i)
	{

		temp[i] = new c_node("NULL", -1.0, -1.0);
	}

	mergeSort_divide(temp, index_i, index_e, level);

	//Delete allocated memory, deleting nodes
	for (int i = 0; i < newSize; ++i)
	{
		if (temp[i] != NULL)
			delete temp[i];
	}

	//delete temp array
	delete[] temp;
}

/****************************************************************************
Description: This function will divide an array into half recursively, until
			there is only one element in each subarray.

output: none.
****************************************************************************/
void PeptidesApp::mergeSort_divide(c_node **temp, int index_i, int index_e, int level)
{
	if (index_i < index_e)
	{

		int center = (index_i + index_e) / 2;
		mergeSort_divide(temp, index_i, center, level);
		mergeSort_divide(temp, center + 1, index_e, level);
		mergeSort_merge(temp, index_i, center + 1, index_e, level);
	}
}

/****************************************************************************
Description: This function will swap data between to array elements.

output: none.
****************************************************************************/
void PeptidesApp::assign_data(c_node **temp, int temp_index, int list_index)
{
	if (temp[temp_index] != NULL)
	{

		temp[temp_index]->peptide = this->peptideDatabase[list_index]->peptide;
		temp[temp_index]->data[0] = this->peptideDatabase[list_index]->data[0];
		temp[temp_index]->data[1] = this->peptideDatabase[list_index]->data[1];
	}
}

/****************************************************************************
Description: This function will take care of the merging process of the 
			mergesort algorithm. Sorted data will be restored to original 
			source.
output: none. 
****************************************************************************/
void PeptidesApp::mergeSort_merge(c_node **temp, int leftPos, int rightPos, int rightEnd, int level)
{
	int leftEnd = rightPos - 1;
	int total_elements = rightEnd - leftPos + 1;
	int tmpPos = 0;
	if (total_elements == size)
		int tmpPos = leftPos; //since elements will be inserted in order(ascending)

	//main loop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{

		if (this->peptideDatabase[leftPos]->data[level] <= this->peptideDatabase[rightPos]->data[level])
		{
			assign_data(temp, tmpPos, leftPos);
			tmpPos++;
			leftPos++;
		}

		else
		{
			assign_data(temp, tmpPos, rightPos);
			tmpPos++;
			rightPos++;
		}

	} //end main loop

	//Will copy rest of the first half
	while (leftPos <= leftEnd)
	{
		assign_data(temp, tmpPos, leftPos);
		tmpPos++;
		leftPos++;
	}

	//will copy rest of right half
	while (rightPos <= rightEnd)
	{
		assign_data(temp, tmpPos, rightPos);
		tmpPos++;
		rightPos++;
	}

	if (total_elements == size)
	{
		//copy temp data to original list
		for (int i = 0; i < total_elements; i++, rightEnd--)
		{
			this->peptideDatabase[rightEnd]->peptide = temp[rightEnd]->peptide;
			this->peptideDatabase[rightEnd]->data[0] = temp[rightEnd]->data[0];
			this->peptideDatabase[rightEnd]->data[1] = temp[rightEnd]->data[1];
		}
	}

	else
	{
		int counter = total_elements - 1;
		//copy temp data to original list
		for (int i = 0; i < total_elements; i++, rightEnd--, counter--)
		{
			this->peptideDatabase[rightEnd]->peptide = temp[counter]->peptide;
			this->peptideDatabase[rightEnd]->data[0] = temp[counter]->data[0];
			this->peptideDatabase[rightEnd]->data[1] = temp[counter]->data[1];
		}
	}
}

void PeptidesApp::printPeptideDatabase()
{
	for (int i = 0; i < this->size; ++i)
	{
		if (this->peptideDatabase[i] != NULL) {
			cout << "Peptide:" << this->peptideDatabase[i]->peptide << ", Mass:"; 
			cout << this->peptideDatabase[i]->data[0];
			cout << ", NET:" << this->peptideDatabase[i]->data[1] << endl;
		}
	}
}