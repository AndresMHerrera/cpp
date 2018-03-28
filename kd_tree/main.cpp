#include "peptides.app.h"

int main(int argc, char const *argv[])
{
	if(argv[1] != NULL && argv[2] != NULL) {
		PeptidesApp app(argv);
	}

	else 
		cout << "usage: peptides databaseFile observedListFile" << endl;

	return 0;
}