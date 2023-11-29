#ifndef TEP3_CNODE_H
#define TEP3_CNODE_H
#include <vector>
#include <string>
#include "../help-functions-and-constants/functions.h"


class cNode {
public:

    cNode();
    cNode(std::string sValue);
    cNode(const cNode &other);
    ~cNode();


    std::vector<cNode*>* vChildren;
    cNode* CParent; //TODO zmienic nazwe na chyba vParent
    std::string sValue;

    void cAddtoNode(cNode &newChild);

    friend class cTree;

private:

};


#endif