#include <iostream>
#include <utility>
#include "../cNode.h"


class cNodeArthOperator : public cNode
{

public:
    std::string operation;
    cNode* leftChild;
    cNode* rightChild;

    explicit cNodeArthOperator(std::string operation) : operation(std::move(operation)), leftChild(nullptr), rightChild(nullptr) {}
    cNodeArthOperator(std::string operation, cNode* leftChild, cNode* rightChild) : operation(std::move(operation)), leftChild(leftChild), rightChild(rightChild) {}

    double compute() const override;

};
