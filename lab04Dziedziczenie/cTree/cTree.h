#include <vector>
#include <string>
#include "../cNode/cNode.h"

class cTree {
public:

    cNode* cRoot; //wskaznik na Roota

    double compute();
    std::vector<std::string> findVariables();
    void printPrefix();
    void printTree();

    cTree& enter(std::vector<std::string> formula);
    cTree& join(cTree& tree);
    cTree& reset();

};

