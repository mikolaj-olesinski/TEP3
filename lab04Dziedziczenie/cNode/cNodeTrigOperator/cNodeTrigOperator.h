#include <iostream>
#include "../cNode.h"


class cNodeTrigOperator : public cNode
{
public:
    std::string operation;
    cNode* child;


    cNodeTrigOperator(std::string operation): operation(operation), child(nullptr) {};
    cNodeTrigOperator(std::string operation, cNode* child): operation(operation), child(child) {};
    cNodeTrigOperator(const cNodeTrigOperator& other): operation(other.operation), child(other.child) {};
    ~cNodeTrigOperator(){delete child;}

    double compute() const override;

};

double cNodeTrigOperator::compute() const
{
    if (operation == "sin") return sin(child->compute());
    else if (operation == "cos") return cos(child->compute());
    else throw std::invalid_argument("Invalid operation");
}
