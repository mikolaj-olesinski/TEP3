#include "cNodeVariable.h"


double cNodeVariable::compute() const
{
    return tempValue;
}

std::string cNodeVariable::getValue() const
{
    return name;
}