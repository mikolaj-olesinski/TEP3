#include "cNode.h"

#include <utility>

int copyCounter = 0; //zmienna globalna przechowujaca ilosc kopiowan (do zadania 5)

cNode::cNode() : vChildren(new std::vector<cNode*>()), cParent(nullptr) {} //konstruktor domyslny


cNode::cNode(std::string value) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(std::move(value)){} //konstruktor z parametrem



cNode::cNode(const cNode &other) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(other.sValue){ //konstruktor kopiujacy
    copyCounter++;
    std::cout << "copyCounter: " << copyCounter << "    value: " << other.sValue << std::endl;
    for (const auto &child : *(other.vChildren)) { // Przeglądamy dzieci innego węzła
        auto *newChild = new cNode(*child);  // Rekurencyjne kopiowanie dzieci
        newChild->cParent = this;  // Ustawiamy rodzica nowego dziecka na siebie
        vChildren->push_back(newChild); // Dodaj nowe dziecko do wektora dzieci
    }
}

// Destruktor
cNode::~cNode() { //destruktor

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

void cNode::cAddtoNode(cNode &newChild) {  //dodaje wezel do wektora dzieci
    vChildren->push_back(&newChild); //dodjemy nowe dziecko do wektora dzieci
    newChild.cParent = this;  // Ustawiamy rodzica nowego dziecka na siebie
}
