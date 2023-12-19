#include <iostream>
#include "cNode/cNodeNumber/cNodeNumber.h"
#include "cNode/cNodeVariable/cNodeVariable.h"
#include "cNode/cNodeArthOperator/cNodeArthOperator.h"
#include "cNode/cNodeTrigOperator/cNodeTrigOperator.h"
#include "cTree/cTree.h"


int main() {

    cTree tree;

    tree.enter({"+", "1", "b"});


    return 0;
}
