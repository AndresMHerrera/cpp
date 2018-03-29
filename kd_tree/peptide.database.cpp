#include "peptide.database.h"

PeptideDatabase::PeptideDatabase(){}

PeptideDatabase::~PeptideDatabase(){}

void PeptideDatabase::insert(string peptide, double mass, double NET)
{
	Peptide entry(peptide, mass, NET);
	this->peptideDatabase.push_back(entry);
}

Peptide PeptideDatabase::get(int index)
{
	return this->peptideDatabase[index];
}

int PeptideDatabase::size()
{
	return this->peptideDatabase.size();
}

// TODO: work on cleaning up the merge sort algorithm.
/****************************************************************************
Description: This function will serve as the driver for the sorting process.
			It will allocate memory for temporary storage, begin the sorting
			process, and free memory allocated. 
output: none.			
****************************************************************************/
void PeptideDatabase::sort(int index_i, int index_e, int level)
{
	//create temp array
	int newSize = (index_e - index_i) + 1;
	vector<Peptide> temp(newSize, Peptide("NULL", -1.0, -1.0));
	this->mergeSort_divide(temp, index_i, index_e, level);
}

/****************************************************************************
Description: This function will divide an array into half recursively, until
			there is only one element in each subarray.

output: none.
****************************************************************************/
void PeptideDatabase::mergeSort_divide(vector<Peptide> &temp, int index_i, int index_e, int level)
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
Description: This function will take care of the merging process of the 
			mergesort algorithm. Sorted data will be restored to original 
			source.
output: none. 
****************************************************************************/
void PeptideDatabase::mergeSort_merge(vector<Peptide> &temp, int leftPos, int rightPos, int rightEnd, int level)
{
	int leftEnd = rightPos - 1;
	int total_elements = rightEnd - leftPos + 1;
	int tmpPos = 0;
	if (total_elements == this->size()) {
		tmpPos = leftPos; //since elements will be inserted in order(ascending)
		// int tmpPos = leftPos; //since elements will be inserted in order(ascending)
	}

	//main loop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (this->peptideDatabase[leftPos].data[level] <= this->peptideDatabase[rightPos].data[level])
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

	if (total_elements == this->size())
	{
		//copy temp data to original list
		for (int i = 0; i < total_elements; i++, rightEnd--)
		{
			this->peptideDatabase[rightEnd].peptide = temp[rightEnd].peptide;
			this->peptideDatabase[rightEnd].data[0] = temp[rightEnd].data[0];
			this->peptideDatabase[rightEnd].data[1] = temp[rightEnd].data[1];
		}
	}

	else
	{
		int counter = total_elements - 1;
		//copy temp data to original list
		for (int i = 0; i < total_elements; i++, rightEnd--, counter--)
		{
			this->peptideDatabase[rightEnd].peptide = temp[counter].peptide;
			this->peptideDatabase[rightEnd].data[0] = temp[counter].data[0];
			this->peptideDatabase[rightEnd].data[1] = temp[counter].data[1];
		}
	}
}

/****************************************************************************
Description: This function will swap data between to array elements.

output: none.
****************************************************************************/
void PeptideDatabase::assign_data(vector<Peptide> &temp, int temp_index, int list_index)
{
	temp[temp_index].peptide = this->peptideDatabase[list_index].peptide;
	temp[temp_index].data[0] = this->peptideDatabase[list_index].data[0];
	temp[temp_index].data[1] = this->peptideDatabase[list_index].data[1];
}
// void PeptideDatabase::assign_data(vector<Peptide> &temp, int temp_index, int list_index)
// {
// 	if (temp[temp_index] != NULL)
// 	{
// 		temp[temp_index]->peptide = this->peptideDatabase[list_index]->peptide;
// 		temp[temp_index]->data[0] = this->peptideDatabase[list_index]->data[0];
// 		temp[temp_index]->data[1] = this->peptideDatabase[list_index]->data[1];
// 	}
// }