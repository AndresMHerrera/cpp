#include "file.reader.h"

FileReader::FileReader() {}

FileReader::~FileReader() {}

// This function will read a file line by line, and return a vector of lines.
vector<string> FileReader::readFileByLine(string fileName)

{
    string line;
    vector<string> result;
    ifstream file;

    file.open(fileName.c_str(), ios_base::in);

    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line, '\n');
            line = this->stringService.trimLeadingAndTrailingSpaces(line);

            if (!line.empty())
            {
                result.push_back(line);
            }
        }

        file.close();
    }

    return result;
}