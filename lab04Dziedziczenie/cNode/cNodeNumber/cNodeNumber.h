#include <iostream>
#include "../cNode.h"

class cNodeNumber : public cNode
{
public:
    double value;

    cNodeNumber(double value): value(value) {};
    cNodeNumber(const cNodeNumber& other): value(other.value) {};

    double compute() const override;
};

double cNodeNumber::compute() const
{
    return value;
}
