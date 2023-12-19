#include <vector>
#include <string>
#include <set>
#include "../cNode/cNode.h"

class cTree {
public:

    cNode* cRoot; //wskaznik na Roota

    double compute() const;

    cNode* createTreeRecursive(std::vector<std::string>& formula);
    cTree& enter(std::vector<std::string> formula);
    cTree& join(const cTree &other);
    cNode* findRightLeafParent() const;

    void initalizeVariables(std::set<std::string> variables);
    std::set<std::string> findVariables() const;

    void printTree() const;
    void printTreeRecursive(cNode* node, const std::string& prefix, bool isLeft) const;

    cTree() : cRoot(nullptr) {};

};

