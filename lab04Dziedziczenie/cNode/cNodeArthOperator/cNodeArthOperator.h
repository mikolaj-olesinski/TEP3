#include <iostream>
#include <utility>
#include "../cNode.h"


class cNodeArthOperator : public cNode
{

public:
    std::string operation;
    cNode* leftChild;
    cNode* rightChild;

    cNodeArthOperator(std::string operation, cNode* leftChild, cNode* rightChild) : operation(std::move(operation)), leftChild(leftChild), rightChild(rightChild) {}

    std::string getValue() const override;
    double compute() const override;

};
