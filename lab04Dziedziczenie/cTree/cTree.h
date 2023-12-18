#include <vector>
#include <string>
#include "../cNode/cNode.h"

class cTree {
public:

    cNode* cRoot; //wskaznik na Roota

    double compute();

    cNode* createTreeRecursive(std::vector<std::string>& formula);
    cTree& enter(std::vector<std::string> formula);

    cTree() : cRoot(nullptr) {};

};

