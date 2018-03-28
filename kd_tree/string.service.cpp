#include "string.service.h"

StringService::StringService(){}

StringService::~StringService(){}

// trim from start
string & StringService::ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
string & StringService::rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
string & StringService::trimLeadingAndTrailingSpaces(std::string &s) {
        return ltrim(rtrim(s));
}

