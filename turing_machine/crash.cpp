#include "crash.h"
#include <stdexcept> //std exceptions includes runtime error
#include <string>
using namespace std;

Crash::Crash(string reason)
    :runtime_error(reason.c_str())           //requires c style string
{
}