#include "cTree.h"

template <typename T>
cTree<T>::cTree(const cTree<T> &other) {
    std::cout << "Copy constructor called" << std::endl;
    if (other.cRoot != nullptr) { //sprawdzamy czy drzewo ktore chcemy skopiowac nie jest puste
        cRoot = new cNode(*other.cRoot); //tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy skopiowac
    } else {
        cRoot = nullptr; //jesli drzewo ktore chcemy skopiowac jest puste to Root nowego drzewa ustawiamy na nullptr
    }
}

template <typename T>
cTree<T>::cTree() {
    cRoot = nullptr; //tworzymy puste drzewo w konstruktorze domyslnym
}

template <typename T>
cTree<T>::~cTree() {
    delete cRoot; //usuwamy pamiec po Root w destruktorze cNode usuwa pamiec po wszystkich dzieciach
}




template <typename T>
cTree<T>& cTree<T>::join(const cTree& other) {
    if (cRoot == nullptr) {
        cRoot = new cNode(*other.cRoot);
        return *this;
    }

    cNode* rightLeafParent = findRightLeafParent();
    rightLeafParent->vChildren->back() = new cNode(*other.cRoot);
    return *this;
}


template <typename T>
T cTree<T>::compute(const std::vector<std::string> valuesOfVariables) const { //obliczanie wartosci drzewa

    return computeNode(cRoot, valuesOfVariables); //obliczamy wartosc drzewa z wykorzystaniem mapy zmiennych i ich wartosci
}

template <typename T>
cTree<T>& cTree<T>::operator=(const cTree<T>& other) { //operator przypisania
    if (this != &other) { //sprawdzamy czy nie przypisujemy do samego siebie
        delete cRoot; //usuwamy pamiec po Root
        cRoot = new cNode(*other.cRoot); //tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy przypisac
    }

    return *this; //zwracamy obiekt cTree
}

template <typename T>
cTree<T>& cTree<T>::operator=(cTree<T>&& other)  noexcept {
    if (this != &other) {
        delete cRoot; //usuwamy pamiec po Root
        cRoot = other.cRoot;
        other.cRoot = nullptr;
    }
    return *this;
}

template <typename T>
cTree<T> cTree<T>::operator+(const cTree<T>& other) const
{
    cTree<T> newTree(*this); //tworzymy nowe drzewo z obecnego
    newTree.join(other); //laczymy nowe drzewo z drugim
    return newTree; // Return the new tree
}


template <typename T>
std::set<std::string> cTree<T>::findVariables() const{
    std::set<std::string> variables; //tworzymy set zmiennych
    cTree::findVariablesRecursive(cRoot, variables); //rekurencyjnie szukamy zmiennych
    return variables; //zwracamy set zmiennych
}


template <typename T>
void cTree<T>::printBT() const {
    cTree::printBTRecursiveHelp("", cRoot, false); //wywolujemy funkcje rekurencyjna wypisujaca drzewo

}

template <typename T>
std::vector<std::string> cTree<T>::getPrefix() const{
    return getPrefixRecursiveHelp(cRoot); //wywolujemy funkcje rekurencyjna pobierajaca prefiks
}