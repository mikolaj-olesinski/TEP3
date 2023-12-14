#include <iostream>
#include "../cNode.h"

class cNodeArthOperator : public cNode
{

public:
    std::string operation;
    cNode* leftChild;
    cNode* rightChild;

    cNodeArthOperator(std::string operation, cNode* left, cNode* right): operation(operation), leftChild(left), rightChild(right) {};
    cNodeArthOperator(const cNodeArthOperator& other): operation(other.operation), leftChild(other.leftChild), rightChild(other.rightChild) {};
    ~cNodeArthOperator(){delete leftChild; delete rightChild;}

    double compute() const override;

};

double cNodeArthOperator::compute() const
{
    if (operation == "+") return leftChild->compute() + rightChild->compute();
    else if (operation == "-") return leftChild->compute() - rightChild->compute();
    else if (operation == "*") return leftChild->compute() * rightChild->compute();
    else if (operation == "/") return leftChild->compute() / rightChild->compute();
    else throw std::invalid_argument("Invalid operation");
}
