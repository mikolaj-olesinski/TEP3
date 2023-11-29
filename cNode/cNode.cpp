
#include "cNode.h"
#include <algorithm>

cNode::cNode() : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue("") {}

cNode::cNode(std::string sValue) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(sValue) {}

cNode::cNode(const cNode &other) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(other.sValue) {
    for (const auto &child : *(other.vChildren)) { // Przeglądamy dzieci innego węzła
        cNode *newChild = new cNode(*child);  // Rekurencyjne kopiowanie dzieci
        newChild->cParent = this;  // Ustawiamy rodzica nowego dziecka na siebie
        vChildren->push_back(newChild); // Dodaj nowe dziecko do wektora dzieci
    }
}

// Destruktor
cNode::~cNode() {

    if (cParent != nullptr) {  // Jeżeli istnieje rodzic
        auto& children = *(cParent->vChildren); // Pobieramy wektor dzieci rodzica
        children.erase(std::remove(children.begin(), children.end(), this), children.end()); // Usuwamy siebie z wektora dzieci rodzica
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
    vChildren->push_back(&newChild); //dodjemy nowe dziecko do wektora dzieci
    newChild.cParent = this;  // Ustawiamy rodzica nowego dziecka na siebie
}



