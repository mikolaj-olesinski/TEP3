#include "cTree.h"

template <typename T>
cTree<T>::cTree(const cTree<T> &other) {
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
cTree<T>& cTree<T>::enter(const std::vector<std::string>& formula) {
    delete cRoot; //usuwamy pamiec po Root
    cRoot = new cNode(formula[0]); //tworzymy nowy obiekt cNode z pierwszym elementem formuly
    cNode* CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    cNode *newAddedNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres nowego wezla ktory bedziemy dodawac do drzewa


    for (int i = 1; i < formula.size(); i++){ //przechodzimy po formule od drugiego elementu bo pierwszy jest juz w Root
        newAddedNode = new cNode(formula[i]); //przypisujemy adres nowego obiektu cNode z kolejnym elementem formuly ktory bedziemy dodawac do drzewa

        int maxAmountOfChildren = fMaxAmountOfChildren(CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora

        if (CurrentNode->vChildren->size() < maxAmountOfChildren) { //sprawdzamy czy aktualny wezel ma mniej niz dana ilosc dzieci
            CurrentNode->cAddtoNode(*newAddedNode); //jesli tak to dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (isOperator(newAddedNode->sValue)) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        }
        else { //jesli aktualny wezel ma juz dopuszczona dzieci to przechodzimy na jego rodzica
            CurrentNode = CurrentNode->cParent;

            maxAmountOfChildren = fMaxAmountOfChildren(CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            while (CurrentNode->vChildren->size() >= maxAmountOfChildren) { //przechodzimy po drzewie az dojdziemy do wezla ktory ma mniej niz dopuszczone ilosc dzieci
                CurrentNode = CurrentNode->cParent;
                maxAmountOfChildren = fMaxAmountOfChildren(CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            }

            CurrentNode->cAddtoNode(*newAddedNode); //dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (isOperator(newAddedNode->sValue)) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        }


    }


    return *this; //zwracamy obiekt cTree
}


template <typename T>
cTree<T>& cTree<T>::join(const cTree& other) {
    if (cRoot == nullptr) { //sprawdzamy czy drzewo do ktorego chcemy dolaczyc jest puste
        cRoot = new cNode(std::move(*other.cRoot)); //jesli tak to tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy dolaczyc
        return *this;
    }

    cNode* rightLeafParent = findRightLeafParent(); //znajdujemy rodzica prawego liscia
    rightLeafParent->vChildren->back() = other.cRoot; //dolaczamy drzewo do rodzica prawego liscia
    return *this; //zwracamy obiekt cTree
}


template <typename T>
T cTree<T>::compute(const std::vector<std::string>& valuesOfVariables) const { //obliczanie wartosci drzewa

    return computeNode(cRoot, valuesOfVariables); //obliczamy wartosc drzewa z wykorzystaniem mapy zmiennych i ich wartosci
}

template <typename T>
cTree<T>& cTree<T>::operator=(const cTree<T>& other) { //operator przypisania
    if (this != &other) { //sprawdzamy czy nie przypisujemy do samego siebie
        delete cRoot; //usuwamy pamiec po Root
        cRoot = new cNode(*other.cRoot); //tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy skopiowac
    }
    return *this; //zwracamy obiekt cTree
}



template <typename T>
cTree<T> cTree<T>::operator+(const cTree<T>& other) const{ //operator dodawania

    cTree *newTree; //tworzymy wskaznik na obiekt cTree w ktroym bedziemy przechowywac adres nowego drzewa
    newTree = new cTree(*this); //tworzymy nowe drzewo z drzewa z ktorym chcemy dodac z konstruktora kopiujacego

    return newTree->join(other); //dolaczamy drzewo z ktorym chcemy dodac i zwracamy nowe drzewo
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