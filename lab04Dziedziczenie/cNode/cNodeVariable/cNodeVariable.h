#include <iostream>
#include "../cNode.h"

class cNodeVariable : public cNode
{
public:
    std::string name;
    double tempValue;

    cNodeVariable(std::string name): name(name){};
    cNodeVariable(const cNodeVariable &other): cNode(other), name(other.name), tempValue(other.tempValue) {};

    double compute() const override;
};

double cNodeVariable::compute() const
{
    return tempValue;
}