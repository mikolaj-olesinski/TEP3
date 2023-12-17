#include "cTree.h"
#include "../helpFucntions/functions.h"
#include "../cNode/cNodeTrigOperator/cNodeTrigOperator.h"
#include "../cNode/cNodeArthOperator/cNodeArthOperator.h"


cTree& cTree::enter(std::vector<std::string> formula) {
    delete cRoot;
    if(isTrigOperator(formula[0])) cRoot = new cNodeTrigOperator(formula[0]);
    else if(isArthOperator(formula[0])) cRoot = new cNodeArthOperator(formula[0]);
    else throw std::invalid_argument("niepoprawny operator"); //TODO zmienic



}
