#include "help-functions-and-constants/functions.h"
#include "cTree/cTree.h"
#include <iostream>

int main() {

    //UI();

    cTree<double> tree;
    tree.enter({"+", "1.1", "2.6"});
    tree.join({"*", "3.2", "z"});
    double a = tree.compute({"4.5"});
    std::cout << a << std::endl;



    return 0;
}





