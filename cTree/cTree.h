

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


template <typename T>
class cTree {
public:

    cTree(const cTree &other); //konstruktor kopiujacy
    cTree(); //konstruktor domyslny
    ~cTree(); //destruktor

    cTree& enter(const std::vector<std::string>& formula); //funkcja tworzaca drzewo z wektora stringow
    cTree& join(const cTree &other); //funkcja laczaca 2 drzewa przyjmujaca jako argument drugie drzewo
    cTree& join(const std::vector<std::string>& formula); //funkcja laczaca 2 drzewa przyjmujaca jako argument wektor stringow


    T compute(const std::vector<std::string> valuesOfVariables) const; //funkcja obliczajaca wartosc drzewa

    cTree& operator=(const cTree& other); //operator przypisania
    cTree operator+(const cTree& other) const; //operator dodawania

    std::set<std::string> findVariables() const; //funkcja znajdujaca zmienne w drzewie
    void findVariablesAndReplace(std::vector<std::string> replaceValues); //funkcja znajdujaca zmienne w drzewie i zamieniajaca je na wartosci z wektora

    void printBT() const; //funkcja wypisujaca drzewo w formie graficznej

    std::vector<std::string> getPrefix() const; //funkcja zwracajaca drzewo w formie prefixowej

    std::string sGetKnownType() const; //funkcja zwracajaca znany typ drzewa




//TODO usunac private:

    cNode<T> *cRoot; //korzen drzewa

    cNode<T>* findRightLeafParent() const; //funkcja znajdujaca prawy lisc
    static void findVariablesRecursive(cNode<T>* currentNode, std::set<std::string>& variables); //funkcja znajdujaca zmienne w drzewie za pomoca rekurencji i przekazujaca je do zbioru
    static void replaceVariableRecursive(cNode<T>* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables); //funkcja zamieniajaca zmienne w drzewie za pomoca rekurencji

    static std::vector<cNode<T>*> getLeavesAtLowestLevel(cNode<T>* node); //funkcja znajdujaca liscie na najnizszym poziomie
    static std::vector<std::vector<cNode<T>*>> segregateLeavesByParent(const std::vector<cNode<T>*>& leaves); //funkcja segregujaca liscie po rodzicach
    static int maxDepth(cNode<T>* root); //funkcja znajdujaca wysokosc drzewa
    static void getLeavesAtDepth(cNode<T>* node, int currentDepth, int targetDepth, std::vector<cNode<T>*>& leavesByParent); //funkcja znajdujaca liscie na danym poziomie


    static void printBTRecursiveHelp(const std::string& prefix, cNode<T>* node, bool isLeft); //funkcja wypisujaca drzewo za pomoca rekurencji
    static std::vector<std::string> getPrefixRecursiveHelp(cNode<T> *node); //funkcja zwracajaca drzewo w formie prefixowej za pomoca rekurencji
};



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
    cRoot = new cNode<T>(formula[0]); //tworzymy nowy obiekt cNode z pierwszym elementem formuly
    cNode<T> *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    cNode<T> *newAddedNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres nowego wezla ktory bedziemy dodawac do drzewa


    for (int i = 1; i < formula.size(); i++){ //przechodzimy po formule od drugiego elementu bo pierwszy jest juz w Root
        newAddedNode = new cNode<T>(formula[i]); //przypisujemy adres nowego obiektu cNode z kolejnym elementem formuly ktory bedziemy dodawac do drzewa

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
        cRoot = new cNode(*other.cRoot); //jesli tak to tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy dolaczyc
        return *this; //zwracamy obiekt cTree
    }

    cNode<T>* rightLeafParent = findRightLeafParent(); // rodzic ostatniego liścia zwracamy rodzica bo inaczej zwracamy kopie wskaznika na liścia
    delete rightLeafParent->vChildren->back(); // Usuwamy ostatnie dziecko rodzica ostatniego liścia
    rightLeafParent->cAddtoNode(*other.cRoot); // Dodajemy nowe dziecko do rodzica ostatniego liścia
    return *this; // Zwracamy nowe drzewo
}

template <typename T>
cTree<T> &cTree<T>::join(const std::vector<std::string> &formula) {
    return join((new cTree)->enter(formula)); //tworzymy nowe drzewo z wektora stringow i laczymy je z aktualnym drzewem
}


template <typename T>
T cTree<T>::compute(const std::vector<std::string> valuesOfVariables) const{

    cTree *Tree = new cTree(*this);

    Tree->findVariablesAndReplace(valuesOfVariables); //zamieniamy zmienne na wartosci


    while (Tree->cRoot != nullptr) { //dopoki nie dojdziemy do Roota

        std::vector<cNode<T> *> leavesAtLowestLevel = cTree::getLeavesAtLowestLevel(Tree->cRoot); //pobieramy liscie na najnizszym poziomie
        std::vector<std::vector<cNode<T> *>> segregatedLeaves = cTree::segregateLeavesByParent(leavesAtLowestLevel); //grupujemy liscie wedlug rodzica
        T value; //zmienna przechowujaca wartosc nowego wezla

        for (const auto &leaves: segregatedLeaves) { //dla kazdej grupy lisci
            T newValue = (leaves[0]->cParent->sValue == "*") ? 1 : 0; //ustawiamy wartosc nowego wezla na 1 lub 0 w zaleznosci od rodzaju operatora

            for (const auto &leaf: leaves) { //dla kazdego liscia w grupie
                std::string parentOperator = leaf->cParent->sValue; //pobieramy rodzaj operatora rodzica

                T value = stod(leaf->sValue); //pobieramy wartosc liscia


                if (parentOperator == "+") { //w zaleznosci od rodzaju operatora rodzica wykonujemy odpowiednie dzialanie
                    newValue += value;
                } else if (parentOperator == "*") {
                    newValue *= value;
                } else if (parentOperator == "-") {
                    newValue -= value;
                } else if (parentOperator == "/") {
                    if (leaf == leaves[0]) newValue = value;
                    else newValue = value / newValue;
                } else if (parentOperator == "cos") {
                    newValue = std::cos(value);
                } else if (parentOperator == "sin") {
                    newValue = std::sin(value);
                }

            }

            if (leaves[0]->cParent->cParent == nullptr) { //jesli rodzic rodzica jest pusty to znaczy ze jestesmy w Root
                delete Tree; //usuwamy pamiec po drzewie
                return newValue; //zwracamy wartosc Roota
            }

            leaves[0]->cParent->sValue =  std::to_string(newValue); //ustawiamy wartosc rodzica rodzica na wartosc nowego wezla

            for (const auto &leaf: leaves) delete leaf; //usuwamy pamiec po lisciach
        }
    }
    return -1; //zwracamy -1 jesli nie udalo sie obliczyc wartosci

}


template <>
std::string cTree<std::string>::compute(const std::vector<std::string> valuesOfVariables) const {

    cTree *Tree = new cTree(*this);


    Tree->findVariablesAndReplace(valuesOfVariables); //zamieniamy zmienne na wartosci


    while (Tree->cRoot != nullptr) { //dopoki nie dojdziemy do Roota

        std::vector<cNode<std::string> *> leavesAtLowestLevel = cTree::getLeavesAtLowestLevel(Tree->cRoot); //pobieramy liscie na najnizszym poziomie
        std::vector<std::vector<cNode<std::string> *>> segregatedLeaves = cTree::segregateLeavesByParent(leavesAtLowestLevel); //grupujemy liscie wedlug rodzica

        for (const auto &leaves: segregatedLeaves) { //dla kazdej grupy lisci
            std::string newValue;
            std::string parentOperator = leaves[0]->cParent->sValue; //pobieramy rodzaj operatora rodzica

            int maxAmountOfChildren = fMaxAmountOfChildren(parentOperator); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora

            if(maxAmountOfChildren == 2){
                if (parentOperator == "+") { //w zaleznosci od rodzaju operatora rodzica wykonujemy odpowiednie dzialanie
                    newValue = addString(leaves[0]->sValue, leaves[1]->sValue);
                } else if (parentOperator == "*") {
                    newValue = mulString(leaves[0]->sValue, leaves[1]->sValue);
                } else if (parentOperator == "-") {
                    newValue = subString(leaves[0]->sValue, leaves[1]->sValue);
                }
                else if (parentOperator == "/") {
                    newValue = divString(leaves[0]->sValue, leaves[1]->sValue);
                }
            }
            leaves[0]->cParent->sValue = newValue; //ustawiamy wartosc rodzica rodzica na wartosc nowego wezla


            if (leaves[0]->cParent->cParent == nullptr) { //jesli rodzic rodzica jest pusty to znaczy ze jestesmy w Root
                delete Tree; //usuwamy pamiec po drzewie
                return newValue; //zwracamy wartosc Roota
            }

            for (const auto &leaf: leaves) delete leaf; //usuwamy pamiec po lisciach

        }
    }
        return ""; //zwracamy "" jesli nie udalo sie obliczyc wartosci

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
void cTree<T>::findVariablesAndReplace(std::vector<std::string> replaceValues){

    std::set<std::string> sFindVariables = findVariables(); //szukamy zmiennych

    for (std::string variable : sFindVariables) { //dla kazdej zmiennej
        cTree::replaceVariableRecursive(cRoot, variable, replaceValues, sFindVariables); //rekurencyjnie zamieniamy zmienne
    }
}


template <typename T>
void cTree<T>::printBT() const {
    cTree::printBTRecursiveHelp("", cRoot, false); //wywolujemy funkcje rekurencyjna wypisujaca drzewo

}


template <typename T>
std::vector<std::string> cTree<T>::getPrefix() const{
    return getPrefixRecursiveHelp(cRoot); //wywolujemy funkcje rekurencyjna pobierajaca prefiks
}

template <typename T>
cNode<T>* cTree<T>::findRightLeafParent() const {
    cNode<T> *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    while (CurrentNode->vChildren->size() != 0) { //przechodzimy po drzewie az dojdziemy do liscia
        CurrentNode = CurrentNode->vChildren->back(); //przechodzimy na ostatnie dziecko
    }
    return CurrentNode->cParent; //zwracamy rodzica liscia
}


template <typename T>
void cTree<T>::findVariablesRecursive(cNode<T>* currentNode, std::set<std::string>& variables){
    if (currentNode == nullptr) { //sprawdzamy czy wezel nie jest pusty
        return; //jesli tak to konczymy
    }

    if (isVariable(currentNode->sValue) && !isOperator(currentNode->sValue)) { //sprawdzamy czy wartosc wezla jest zmienna i czy nie jest operatorem
        variables.insert(currentNode->sValue); //jesli tak to dodajemy do zbioru zmiennych
    }

    for (cNode<T>* child : *(currentNode->vChildren)) { //przechodzimy po wszystkich dzieciach wezla
        findVariablesRecursive(child, variables); //rekurencyjnie szukamy zmiennych
    }

}

template <>
void cTree<std::string>::findVariablesRecursive(cNode<std::string>* currentNode, std::set<std::string>& variables){
    if (currentNode == nullptr) { //sprawdzamy czy wezel nie jest pusty
        return; //jesli tak to konczymy
    }

    if (isStringVariable(currentNode->sValue) && !isOperator(currentNode->sValue)) { //sprawdzamy czy wartosc wezla jest zmienna i czy nie jest operatorem
        variables.insert(currentNode->sValue); //jesli tak to dodajemy do zbioru zmiennych
    }

    for (cNode<std::string>* child : *(currentNode->vChildren)) { //przechodzimy po wszystkich dzieciach wezla
        findVariablesRecursive(child, variables); //rekurencyjnie szukamy zmiennych
    }

}


template <typename T>
void cTree<T>::replaceVariableRecursive(cNode<T>* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables){
    if (currentNode == nullptr) { //sprawdzamy czy wezel nie jest pusty
        return; //jesli tak to konczymy
    }
    if (currentNode->sValue == variable) { //sprawdzamy czy wartosc wezla jest zmienna
        currentNode->sValue = (replaceValues[std::distance(findVariables.begin(), findVariables.find(variable))]); //jesli tak to zamieniamy na wartosc z wektora wartosci
    }
    for (cNode<T>* child : *currentNode->vChildren) { //przechodzimy po wszystkich dzieciach wezla
        replaceVariableRecursive(child, variable, replaceValues, findVariables); //rekurencyjnie zamieniamy zmienne
    }
}


template <typename T>
std::vector<cNode<T>*> cTree<T>::getLeavesAtLowestLevel(cNode<T>* root) {
    std::vector<cNode<T>*> leaves; // wektor liści
    int iMaxDepth = cTree::maxDepth(root); // maksymalna głębokość drzewa

    if (iMaxDepth > 0) { // jeśli drzewo nie jest puste
        cTree::getLeavesAtDepth(root, 0, iMaxDepth - 1, leaves); // pobieramy liście na ostatniej głębokości
    }

    return leaves; // zwracamy wektor liści
}


template <typename T>
std::vector<std::vector<cNode<T>*>> cTree<T>::segregateLeavesByParent(const std::vector<cNode<T>*>& leaves) {
    std::vector<std::vector<cNode<T>*>> segregatedLeaves; // wektor wektorów liści

    std::map<cNode<T>*, std::vector<cNode<T>*>> leavesByParent; // mapa liści według rodzica

    // Grupowanie liści według rodzica
    for (const auto& leaf : leaves) { // dla każdego liścia
        if (leaf->cParent != nullptr) { // jeśli liść ma rodzica
            cNode<T>* parent = leaf->cParent; // pobieramy rodzica
            leavesByParent[parent].push_back(leaf); // i dodajemy do mapy
        }
    }

    // Konwersja mapy na wektor wektorów
    for (const auto& pair : leavesByParent) { // dla każdej pary rodzic - liście
        segregatedLeaves.push_back(pair.second); // dodajemy do wektora wektorów
    }

    return segregatedLeaves; // zwracamy wektor wektorów
}


template <typename T>
int cTree<T>::maxDepth(cNode<T>* root) {
    if (!root) return 0; // jeśli nie ma korzenia, to głębokość drzewa wynosi 0

    int maxChildDepth = 0; // głębokość najgłębszego dziecka

    for (cNode<T>* child : *(root->vChildren)) { // dla każdego dziecka korzenia
        int childDepth = cTree::maxDepth(child); // obliczamy głębokość uzywajac rekurencji
        maxChildDepth = std::max(maxChildDepth, childDepth); // i wybieramy największą
    }

    return maxChildDepth + 1; // głębokość korzenia to głębokość najgłębszego dziecka + 1
}


template <typename T>
void cTree<T>::getLeavesAtDepth(cNode<T>* node, int currentDepth, int targetDepth, std::vector<cNode<T>*>& leaves) {
    if (!node) return; // jeśli nie ma korzenia, to głębokość drzewa wynosi 0

    if (currentDepth == targetDepth && node->vChildren->empty()) { // jeśli jesteśmy na docelowej głębokości i nie ma dzieci, to dodajemy do wektora
        leaves.push_back(node); // dodajemy do wektora
        return; // i kończymy
    }

    for (cNode<T>* child : *(node->vChildren)) { // dla każdego dziecka korzenia
        cTree::getLeavesAtDepth(child, currentDepth + 1, targetDepth, leaves); // obliczamy głębokość uzywajac rekurencji
    }
}


template <typename T>
void cTree<T>::printBTRecursiveHelp(const std::string &prefix, cNode<T> *node, bool isLeft) {
    if (node != nullptr) { //sprawdzamy czy wezel nie jest pusty
        std::cout << prefix; //wypisujemy prefix

        std::cout << (isLeft ? "|--" : "`--"); //wypisujemy odpowiedni znak w zaleznosci czy jest to lewe czy prawe dziecko

        std::cout << node->sValue << std::endl; //wypisujemy wartosc wezla

        if (node->vChildren != nullptr && !node->vChildren->empty()) { //sprawdzamy czy wezel ma dzieci
            for (size_t i = 0; i < node->vChildren->size(); ++i) { //przechodzimy po wszystkich dzieciach wezla
                cTree::printBTRecursiveHelp(prefix + (isLeft ? "|   " : "    "), (*node->vChildren)[i],i < node->vChildren->size() - 1); //rekurencyjnie wypisujemy wszystkie dzieci wezla
            }
        }
    }
}


template <typename T>
std::vector<std::string> cTree<T>::getPrefixRecursiveHelp(cNode<T> *node) {
    std::vector<std::string> prefix; //tworzymy wektor w ktorym bedziemy przechowywac prefiks
    if (node != nullptr) { //sprawdzamy czy wezel nie jest pusty
        prefix.push_back(node->sValue); //dodajemy wartosc wezla do wektora prefiksu

        if (node->vChildren != nullptr && !node->vChildren->empty()) { //sprawdzamy czy wezel ma dzieci
            for (size_t i = 0; i < node->vChildren->size(); ++i) { //przechodzimy po wszystkich dzieciach wezla
                std::vector<std::string> temp = getPrefixRecursiveHelp((*node->vChildren)[i]); //rekurencyjnie pobieramy prefiks z kazdego dziecka wezla, na nowo tworzac wektor prefiksu
                prefix.insert(prefix.end(), temp.begin(), temp.end()); //dodajemy prefiks z dziecka do prefiksu
            }
        }
    }
    return prefix; //zwracamy wektor prefiksu
}

template <>
std::string cTree<std::string>::sGetKnownType() const {
    return "string"; //zwracamy znany typ drzewa
}

template <>
std::string cTree<int>::sGetKnownType() const {
    return "int"; //zwracamy znany typ drzewa
}

template <>
std::string cTree<double>::sGetKnownType() const {
    return "double"; //zwracamy znany typ drzewa
}


#endif
