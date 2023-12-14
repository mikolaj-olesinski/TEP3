#include <vector>
#include "../cNode/cNode.h"

class cTree {
public:

    cNode* root;

    double compute();
    std::vector<std::string> findVariables();
    void printPrefix();
    void printTree();

    cTree enter(std::vector<std::string> formula);


};

