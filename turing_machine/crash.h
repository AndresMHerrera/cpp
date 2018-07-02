/*
* Description:this class will be used to handle exceptions
*
* Input: <input vars>
*
* Ouput: <expected output>
*/

#ifndef CRASH_H
#define CRASH_H
#include <stdexcept>
#include <string>
using namespace std;

class Crash: public runtime_error
{
public:
    Crash(string reason);
};


#endif