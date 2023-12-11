#ifndef TEP3_CNODE_H
#define TEP3_CNODE_H
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "../help-functions-and-constants/functions.h"



template <typename T>
class cNode {

private:

    cNode(); //konstruktor prywany
    cNode(std::string value); //konstruktor z parametrem
    cNode(const cNode &other); //konstruktor kopiujacy
    ~cNode(); //destruktor


    std::vector<cNode*>* vChildren; //wektor dzieci
    cNode* cParent; //wskaznik na rodzica
    std::string sValue; //wartosc wezla w Stringu

    void cAddtoNode(cNode &newChild); //dodaje wezel do wektora dzieci


    template <typename U>
    friend class cTree; //deklaracja przyjazni z klasa cTree //TODO nie jestem pewien wciaz

};


template <typename T>
cNode<T>::cNode() : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(""){}

template<typename T>
cNode<T> ::cNode(std::string value) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(value){}


template <typename T>
cNode<T>::cNode(const cNode &other) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(other.sValue){
    for (const auto &child : *(other.vChildren)) { // Przeglądamy dzieci innego węzła
        cNode *newChild = new cNode(*child);  // Rekurencyjne kopiowanie dzieci
        newChild->cParent = this;  // Ustawiamy rodzica nowego dziecka na siebie
        vChildren->push_back(newChild); // Dodaj nowe dziecko do wektora dzieci
    }
}

// Destruktor
template <typename T>
cNode<T>::~cNode() {

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


template <typename T>
void cNode<T>::cAddtoNode(cNode &newChild) {
    vChildren->push_back(&newChild); //dodjemy nowe dziecko do wektora dzieci
    newChild.cParent = this;  // Ustawiamy rodzica nowego dziecka na siebie
}


#endif