// Merge sort algorithm source : Mark Allen Weiss "Data Structures and Algorithm Analysis in C++"

#ifndef PEPTIDE_DATABASE_INCLUDED
#define PEPTIDE_DATABASE_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <vector>
#include "file.reader.h"
#include "string.service.h"
using namespace std;

#define DATA_SIZE 2
#define MASS_INDEX 0
#define NET_INDEX 1

// struct Peptide
// {
//     string peptide;
//     double *data; // data[0] == mass, data[1] == NET

//     Peptide(string peptide, double mass, double NET)
//     {
//         data = new double[DATA_SIZE];
//         data[0] = mass;
//         data[1] = NET;
//         this->peptide = peptide;
//     }
//     ~Peptide()
//     {
//         // delete[] data;
//     }
// };

struct Peptide
{
    string peptide;
    vector<double> data; // data[0] == mass, data[1] == NET

    Peptide(string peptide, double mass, double NET)
    {
        data.push_back(mass);
        data.push_back(NET);
        this->peptide = peptide;
    }
};

class PeptideDatabase
{
  private:
    vector<Peptide> peptideDatabase;

    void mergeSort_divide(vector<Peptide> &temp, int index_i, int index_e, int level);
    void mergeSort_merge(vector<Peptide> &temp, int leftPos, int rightPos, int rightEnd, int level);
    void assign_data(vector<Peptide> &temp, int temp_index, int list_index);

  public:
    PeptideDatabase();
    ~PeptideDatabase();

    void insert(string peptide, double mass, double NET);
    Peptide get(int index);
    int size();
    void sort(int index_i, int index_e, int level);
};

#endif