Create a program called “peptides” that will create a k-d tree from a peptide database (comma
separated value formatted file) based on mass and normalized elution time (NET). The file will contain a
list of peptide sequence strings and NET. Your program should compute the mass of a peptide based on
the amino acid characters. You must create a hash table, including the hash function, to do so. You may
not use a map or data structure from the standard template library. Use the monoisotopic mass from
the table at the end of this document.

The program should also read a file containing list of 2-D points of mass and NET, called the observed
list. Each item in this file will also have a number called the ID (for index).
Then for each item in the observed list, perform a nearest neighbor search returning the closest peptide
sequence and elution time. Your program should print (in CSV format) to standard output the list of all
found peptides. Your distance function should be a Euclidean distance based on mass and NET.

Your program will be run as following:
> peptides peptideDatabase.csv observedList.csv



Example Output:

Observed ID, Peptide, NET, Mass, Observed NET, Observed Mass
0, AGGVGGK, 0.149477, 526.286, 0.149477, 544.297
1, APTAAAK, 0.147069, 610.344, 0.148265, 609.294
2, AHYGGF, 0.203524, 632.271, 0.147069, 628.354
3, AHYGGF, 0.203524, 632.271, 0.1494, 630.334
4, FACSNK, 0.158351, 650.285, 0.203524, 650.281
5, TAAPPPK, 0.189039, 662.375, 0.199178, 664.354
6, DGTLASK, 0.165657, 672.344, 0.166774, 671.379
7, DGTLASK, 0.165657, 672.344, 0.0847617, 672.344
8, DGTLASK, 0.165657, 672.344, 0.188473, 672.371
9, DGTLASK, 0.165657, 672.344, 0.162198, 672.381
10, DGTLASK, 0.165657, 672.344, 0.119749, 674.36
11, DGTLASK, 0.165657, 672.344, 0.245981, 675.326
12, QMLCTC, 0.182371, 679.249, 0.11773, 676.376


