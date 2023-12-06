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

public: //TODO: zmienic na private

    cNode(); //konstruktor prywany
    cNode(std::string value); //konstruktor z parametrem
    cNode(const cNode &other); //konstruktor kopiujacy
    ~cNode(); //destruktor


    std::vector<cNode*>* vChildren; //wektor dzieci
    cNode* cParent; //wskaznik na rodzica
    std::string sValue; //wartosc wezla w Stringu
    T tValue; //wartosc wezla w typie T

    void cAddtoNode(cNode &newChild); //dodaje wezel do wektora dzieci

    std::string sGetKnownType() const; //zwraca znany typ zmiennej

    //friend class cTree; //deklaracja przyjazni z klasa cTree //TODO odkomentowacq

};


template <typename T>
cNode<T>::cNode() : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(""){}

template<>
cNode<double> ::cNode(std::string value) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(value) {
    if (isNumber(value)) tValue = std::stod(value); //TODO zmenic na isDouble
}

template<>
cNode<int> ::cNode(std::string value) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(value) {
    if (isNumber(value)) tValue = std::stoi(value); //TODO zmenic na isInt
}

template<>
cNode<std::string> ::cNode(std::string value) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(value) {
    if (isString(value)) tValue = value;
}




template <typename T>
cNode<T>::cNode(const cNode &other) : vChildren(new std::vector<cNode*>()), cParent(nullptr), sValue(other.sValue), tValue(other.tValue) {
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


template <>
std::string cNode<double>::sGetKnownType() const { //TODO bylo inline ogarnac co to
    return "double";
}

template <>
std::string cNode<int>::sGetKnownType() const {
    return "int";
}

template <>
std::string cNode<std::string>::sGetKnownType() const {
    return "string";
}

template <typename T>
std::string cNode<T>::sGetKnownType() const {
    return "unknown";
}

#endif