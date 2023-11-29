

#ifndef TEP3_CTREE_H
#define TEP3_CTREE_H

#include <string>
#include "../cNode/cNode.h"
#include <set>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>


class cTree {
public:
    explicit cTree(cNode &cRoot);
    cTree(cTree &other);
    cTree();
    ~cTree();

    cNode *cRoot;

    cTree join( std::vector<std::string> formula);
    cTree join(cTree &other);

    int compute( std::vector<std::string> formula);

    cTree& operator=(const cTree& other);
    cTree operator+(cTree& other);

    std::set<std::string> findVariables() const;
    void findVariablesAndReplace(std::vector<std::string> replaceValues);

    cTree enter( std::vector<std::string> formula);

private:
    cNode * findRightLeaf() const;
    cNode * findRightLeaf(cTree &tree) const;
    void findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables) const;
    void replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables);

};

void printBT(const std::string& prefix, cNode* node, bool isLeft);
void printBT(cNode* root);

std::vector<std::string> printPrefix(cNode* node);

cTree enter( std::vector<std::string> formula);

int maxDepth(cNode* node);
void getLeavesAtDepth(cNode* node, int currentDepth, int targetDepth, std::vector<cNode*>& leavesByParent);
std::vector<cNode*> getLeavesAtLowestLevel(cNode* node);
std::vector<std::vector<cNode*>> segregateLeavesByParent(const std::vector<cNode*>& leaves);




#endif
