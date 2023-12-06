#include "help-functions-and-constants/functions.h"
#include "cTree/cTree.h"
#include <iostream>

int main() {

    //UI();

    cTree<double> tree;
    tree.enter({"/", "-1", "2"});
    double a = tree.compute({});
    std::cout << a << std::endl;



    return 0;
}




