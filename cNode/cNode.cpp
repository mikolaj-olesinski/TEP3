
#include "cNode.h"
#include <algorithm>

cNode::cNode() : vChildren(new std::vector<cNode*>()), CParent(nullptr), sValue("") {}

cNode::cNode(std::string sValue) : vChildren(new std::vector<cNode*>()), CParent(nullptr), sValue(sValue) {}

cNode::cNode(const cNode &other) : vChildren(new std::vector<cNode*>()), CParent(nullptr), sValue(other.sValue) {
    for (const auto &child : *(other.vChildren)) {
        cNode *newChild = new cNode(*child);  // Rekurencyjne kopiowanie dzieci
        newChild->CParent = this;  // Ustaw nowe dziecko na bieżącego rodzica
        vChildren->push_back(newChild);
    }
}

// Destruktor
cNode::~cNode() {
    // Jeżeli mamy rodzica, usuwamy siebie z jego listy dzieci
    if (CParent != nullptr) {
        auto& children = *(CParent->vChildren);
        children.erase(std::remove(children.begin(), children.end(), this), children.end()); //TODO zrozumiec to
    }

    // Usuwamy dzieci (jeżeli istnieją)
    if (vChildren != nullptr) {
        for (cNode* child : *vChildren) {
            delete child;
        }
        delete vChildren;
    }
}



void cNode::cAddtoNode(cNode &newChild) {
    vChildren->push_back(&newChild);
    newChild.CParent = this;
}



