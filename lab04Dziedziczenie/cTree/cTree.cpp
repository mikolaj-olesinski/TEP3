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

    std::string token = formula.front();
    formula.erase(formula.begin());

    if (isArthOperator(token)) {
        cNode* left = createTreeRecursive(formula);
        cNode* right = createTreeRecursive(formula);
        return new cNodeArthOperator(token, left, right);
    } else if (isTrigOperator(token)) {
        cNode* child = createTreeRecursive(formula);
        return new cNodeTrigOperator(token, child);
    } else if (isVariable(token)) {
        return new cNodeVariable(token);
    } else {
        return new cNodeNumber(std::stod(token));
    }
}

double cTree::compute() {
    return cRoot->compute();
}