#include "help-functions-and-constants/functions.h"
#include "cTree/cTree.h"
#include <iostream>

int main() {

    //UI();

    cTree<std::string> tree;
    tree.enter({"+", "aaa", "bbb"});
    tree.join({"+", "bbb", "ccc"});
    std::string a = tree.compute({});
    std::cout << a << std::endl;



    return 0;
}

//TODO dzielenie



