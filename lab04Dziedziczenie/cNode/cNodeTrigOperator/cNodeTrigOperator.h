#include <iostream>
#include <cmath>
#include <utility>
#include "../cNode.h"


class cNodeTrigOperator : public cNode
{
public:
    std::string operation;
    cNode* child;

    explicit cNodeTrigOperator(std::string operation) : operation(std::move(operation)), child(nullptr) {}
    explicit cNodeTrigOperator(std::string operation, cNode* child) : operation(std::move(operation)), child(child) {}


    std::string getValue() const override;
    double compute() const override;

};


