#include <stringFunctions.h>

//Converts a double into a  string
std::string toString(double x)
{
    std::stringstream ss;
    ss << x;
    return ss.str();
}
