#include "cNodeArthOperator.h"


double cNodeArthOperator::compute() const
{
    if (operation == "+") return leftChild->compute() + rightChild->compute();
    else if (operation == "-") return leftChild->compute() - rightChild->compute();
    else if (operation == "*") return leftChild->compute() * rightChild->compute();
    else if (operation == "/") return leftChild->compute() / rightChild->compute();
    else throw std::invalid_argument("Invalid operation");
}

std::string cNodeArthOperator::getValue() const
{
    return operation;
}
