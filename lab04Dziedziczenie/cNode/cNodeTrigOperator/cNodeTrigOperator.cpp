#include "cNodeTrigOperator.h"

double cNodeTrigOperator::compute() const
{
    if (operation == "sin") return sin(child->compute());
    else if (operation == "cos") return cos(child->compute());
    else throw std::invalid_argument("Invalid operation");
}