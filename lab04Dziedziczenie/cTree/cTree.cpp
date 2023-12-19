#include "cTree.h"
#include "../helpFucntions/functions.h"
#include "../cNode/cNodeTrigOperator/cNodeTrigOperator.h"
#include "../cNode/cNodeArthOperator/cNodeArthOperator.h"
#include "../cNode/cNodeVariable/cNodeVariable.h"
#include "../cNode/cNodeNumber/cNodeNumber.h"


cTree& cTree::enter(std::vector<std::string> formula) {
    delete cRoot;
    cRoot = createTreeRecursive(formula);
    return *this;
}


cNode* cTree::createTreeRecursive(std::vector<std::string>& formula) {

    std::string currentExpression = formula.front();
    formula.erase(formula.begin());

    if (isArthOperator(currentExpression)) {
        cNode* left = createTreeRecursive(formula);
        cNode* right = createTreeRecursive(formula);
        return new cNodeArthOperator(currentExpression, left, right);
    } else if (isTrigOperator(currentExpression)) {
        cNode* child = createTreeRecursive(formula);
        return new cNodeTrigOperator(currentExpression, child);
    } else if (isVariable(currentExpression)) {
        return new cNodeVariable(currentExpression);
    } else {
        return new cNodeNumber(std::stod(currentExpression));
    }
}

double cTree::compute() const{
    return cRoot->compute();
}



void cTree::printTreeRecursive(cNode* node, const std::string& prefix, bool isLeft) const {
    if (node == nullptr) {
        return;
    }

    std::cout << prefix << (isLeft ? "|--" : "`--") << node->getValue() << std::endl;

    if (dynamic_cast<cNodeArthOperator*>(node)) {
        printTreeRecursive(dynamic_cast<cNodeArthOperator*>(node)->leftChild, prefix + "   ", true);
        printTreeRecursive(dynamic_cast<cNodeArthOperator*>(node)->rightChild, prefix + "    ", false);
    } else if (dynamic_cast<cNodeTrigOperator*>(node)) {
        printTreeRecursive(dynamic_cast<cNodeTrigOperator*>(node)->child, prefix + "|   ", true);
    }
}

cNode* cTree::findRightLeafParent() const {
    cNode* current = cRoot;

    while (dynamic_cast<cNodeArthOperator*>(current) || dynamic_cast<cNodeTrigOperator*>(current)) {
        if (dynamic_cast<cNodeArthOperator*>(current)) {
            current = dynamic_cast<cNodeArthOperator*>(current)->rightChild;
        } else if (dynamic_cast<cNodeTrigOperator*>(current)) {
            current = dynamic_cast<cNodeTrigOperator*>(current)->child;
        }
    }
    return current;
}

std::set<std::string> cTree::findVariables() const {
    std::set<std::string> variables;
    cNode* current = cRoot;

    while (dynamic_cast<cNodeArthOperator*>(current) || dynamic_cast<cNodeTrigOperator*>(current)) {
        if (dynamic_cast<cNodeArthOperator*>(current)) {
            if (dynamic_cast<cNodeVariable*>(dynamic_cast<cNodeArthOperator*>(current)->leftChild)) {
                variables.insert(dynamic_cast<cNodeVariable*>(dynamic_cast<cNodeArthOperator*>(current)->leftChild)->getValue());
            }
            current = dynamic_cast<cNodeArthOperator*>(current)->rightChild;
        } else if (dynamic_cast<cNodeTrigOperator*>(current)) {
            current = dynamic_cast<cNodeTrigOperator*>(current)->child;
        }
    }
    if (dynamic_cast<cNodeVariable*>(current)) {
        variables.insert(dynamic_cast<cNodeVariable*>(current)->getValue());
    }
    return variables;
}




