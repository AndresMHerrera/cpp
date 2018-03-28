#ifndef FILE_READER_INCLUDED
#define FILE_READER_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "string.service.h"
using namespace std;

class FileReader
{
  private:
    StringService stringService;

  public:
    FileReader();
    ~FileReader();
    vector<string> readFileByLine(string fileName);
};

#endif