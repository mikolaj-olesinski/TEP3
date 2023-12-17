#include "help-functions-and-constants/UI.tpp"
#include "cTree/cTree.h"

int main() {

    //startUIAndDetermineTypeOfTree();

    cTree<int> tree1, tree2, result;
    tree1.enter({"+", "1", "2"});
    tree2.enter({"+", "3", "4"});
    result = tree1 + tree2;
    result.printBT();


    return 0;
}

