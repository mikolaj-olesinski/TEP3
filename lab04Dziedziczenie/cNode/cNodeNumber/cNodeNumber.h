#include <iostream>
#include "../cNode.h"

class cNodeNumber : public cNode
{
public:
    double value;

    explicit cNodeNumber(double value) : value(value) {};

    std::string getValue() const override;
    double compute() const override;
};
