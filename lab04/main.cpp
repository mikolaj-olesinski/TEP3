#include "help-functions-and-constants/UI.tpp"

int main() {

    cTree<int> tree1, tree2, result;
    tree1.enter({"+", "1", "2"});
    tree2.enter({"+", "3", "4"});
    result.printBT();

    result = tree1 + tree2;

    return 0;
}

