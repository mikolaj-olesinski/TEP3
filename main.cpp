#include "help-functions-and-constants/functions.h"
#include "cTree/cTree.h"
#include <iostream>

int main() {

    //UI();

    cTree<std::string> tree;
    tree.enter({"*", "alaxalaxala", "la"});
    std::string a = tree.compute({});
    std::cout << a << std::endl;




    return 0;
}

//TODO dzielenie



