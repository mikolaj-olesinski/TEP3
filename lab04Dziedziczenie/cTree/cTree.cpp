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


//TODO zmienic to
void cTree::printTreeRecursive(cNode* node, const std::string& prefix, bool isLeft) const {
    if (node == nullptr) {
        return;
    }

    std::cout << prefix << (isLeft ? "|--" : "`--") << node->getValue() << std::endl;

    cNodeArthOperator* arthNode = dynamic_cast<cNodeArthOperator*>(node);
    cNodeTrigOperator* trigNode = dynamic_cast<cNodeTrigOperator*>(node);

    if (arthNode) {
        printTreeRecursive(arthNode->leftChild, prefix + "|   ", true);
        printTreeRecursive(arthNode->rightChild, prefix + "    ", false);
    } else if (trigNode) {
        printTreeRecursive(trigNode->child, prefix + "|   ", true);
    }
}


void cTree::printTree() const {
    printTreeRecursive(cRoot, "", true);
}




