#include "cNodeNumber.h"

double cNodeNumber::compute() const
{
    return value;
}

std::string cNodeNumber::getValue() const
{
    return std::to_string(value);
}
