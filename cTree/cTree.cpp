#include "cTree.h"

#include <utility>


cTree::cTree(cNode &newRoot) {
    cRoot = &newRoot; //przypisujemy adres nowego obiektu cNode do Roota
}

cTree::cTree(const cTree &other) {
    if (other.cRoot != nullptr) { //sprawdzamy czy drzewo ktore chcemy skopiowac nie jest puste
        cRoot = new cNode(*other.cRoot); //tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy skopiowac
    } else {
        cRoot = nullptr; //jesli drzewo ktore chcemy skopiowac jest puste to Root nowego drzewa ustawiamy na nullptr
    }
}

cTree::cTree() {
    cRoot = nullptr; //tworzymy puste drzewo w konstruktorze domyslnym
}

cTree::~cTree() {
    delete cRoot; //usuwamy pamiec po Root w destruktorze cNode usuwa pamiec po wszystkich dzieciach
}


cTree& cTree::enter(const std::vector<std::string>& formula) {
    cRoot = new cNode(formula[0]); //tworzymy nowy obiekt cNode z pierwszym elementem formuly
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
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


cTree& cTree::join(const cTree& other) {
    if (cRoot == nullptr) { //sprawdzamy czy drzewo do ktorego chcemy dolaczyc jest puste
        cRoot = new cNode(*other.cRoot); //jesli tak to tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy dolaczyc
        return *this; //zwracamy obiekt cTree
    }

    cNode* rightLeafParent = findRightLeafParent(); // rodzic ostatniego liścia zwracamy rodzica bo inaczej zwracamy kopie wskaznika na liścia
    delete rightLeafParent->vChildren->back(); // Usuwamy ostatnie dziecko rodzica ostatniego liścia
    rightLeafParent->cAddtoNode(*other.cRoot); // Dodajemy nowe dziecko do rodzica ostatniego liścia
    return *this; // Zwracamy nowe drzewo
}

cTree &cTree::join(const std::vector<std::string> &formula) {
    return join((new cTree)->enter(formula)); //tworzymy nowe drzewo z wektora stringow i laczymy je z aktualnym drzewem
}



int cTree::compute(const std::vector<std::string> formula) const{

    cTree *Tree = new cTree(*this);

    Tree->findVariablesAndReplace(formula); //zamieniamy zmienne na wartosci


    while (Tree->cRoot != nullptr) { //dopoki nie dojdziemy do Roota

        std::vector<cNode *> leavesAtLowestLevel = cTree::getLeavesAtLowestLevel(Tree->cRoot); //pobieramy liscie na najnizszym poziomie
        std::vector<std::vector<cNode *>> segregatedLeaves = cTree::segregateLeavesByParent(leavesAtLowestLevel); //grupujemy liscie wedlug rodzica

        for (const auto &leaves: segregatedLeaves) { //dla kazdej grupy lisci
            int newValue = (leaves[0]->cParent->sValue == "*") ? 1 : 0; //ustawiamy wartosc nowego wezla na 1 lub 0 w zaleznosci od rodzaju operatora

            for (const auto &leaf: leaves) { //dla kazdego liscia w grupie
                std::string parentOperator = leaf->cParent->sValue; //pobieramy rodzaj operatora rodzica


                if (parentOperator == "+") { //w zaleznosci od rodzaju operatora rodzica wykonujemy odpowiednie dzialanie
                    newValue += std::stoi(leaf->sValue);
                } else if (parentOperator == "*") {
                    newValue *= std::stoi(leaf->sValue);
                } else if (parentOperator == "-") {
                    newValue -= std::stoi(leaf->sValue);
                } else if (parentOperator == "cos") {
                    newValue = std::cos(std::stoi(leaf->sValue));
                } else if (parentOperator == "sin") {
                    newValue = std::sin(std::stoi(leaf->sValue));
                }

            }

            if (leaves[0]->cParent->cParent == nullptr) { //jesli rodzic rodzica jest pusty to znaczy ze jestesmy w Root
                delete Tree; //usuwamy pamiec po drzewie
                return newValue; //zwracamy wartosc Roota
            }

            leaves[0]->cParent->sValue = std::to_string(newValue); //ustawiamy wartosc rodzica rodzica na wartosc nowego wezla


            for (const auto &leaf: leaves) delete leaf; //usuwamy pamiec po lisciach
        }
    }
    return -1; //zwracamy -1 jesli nie udalo sie obliczyc wartosci

}


cTree& cTree::operator=(const cTree& other) { //operator przypisania
    if (this != &other) { //sprawdzamy czy nie przypisujemy do samego siebie
        delete cRoot; //usuwamy pamiec po Root
        cRoot = new cNode(*other.cRoot); //tworzymy nowy obiekt cNode z Roota drzewa ktore chcemy skopiowac
    }
    return *this; //zwracamy obiekt cTree
}


cTree cTree::operator+(const cTree& other) const{ //operator dodawania

    cTree *newTree; //tworzymy wskaznik na obiekt cTree w ktroym bedziemy przechowywac adres nowego drzewa
    newTree = new cTree(*this); //tworzymy nowe drzewo z drzewa z ktorym chcemy dodac z konstruktora kopiujacego

    return newTree->join(other); //dolaczamy drzewo z ktorym chcemy dodac i zwracamy nowe drzewo
}


std::set<std::string> cTree::findVariables() const{
    std::set<std::string> variables; //tworzymy set zmiennych
    cTree::findVariablesRecursive(cRoot, variables); //rekurencyjnie szukamy zmiennych
    return variables; //zwracamy set zmiennych
}


void cTree::findVariablesAndReplace(std::vector<std::string> replaceValues){

    std::set<std::string> sFindVariables = findVariables(); //szukamy zmiennych

    for (std::string variable : sFindVariables) { //dla kazdej zmiennej
        cTree::replaceVariableRecursive(cRoot, variable, replaceValues, sFindVariables); //rekurencyjnie zamieniamy zmienne
    }
}


void cTree::printBT() const {
    cTree::printBTRecursiveHelp("", cRoot, false); //wywolujemy funkcje rekurencyjna wypisujaca drzewo

}


std::vector<std::string> cTree::getPrefix() const{
    return getPrefixRecursiveHelp(cRoot); //wywolujemy funkcje rekurencyjna pobierajaca prefiks
}





