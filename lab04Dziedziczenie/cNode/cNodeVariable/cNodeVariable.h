#include <iostream>
#include <utility>
#include "../cNode.h"


class cNodeVariable : public cNode
{
public:
    std::string name;
    double tempValue;

    explicit cNodeVariable(std::string name): name(std::move(name)), tempValue(0) {};

    std::string getValue() const override;
    double compute() const override;
};
