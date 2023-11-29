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

cTree& cTree::enter( std::vector<std::string> formula){
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


cNode* cTree::findRightLeaf() const {
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    while (CurrentNode->vChildren->size() > 1) { //przechodzimy po drzewie az dojdziemy do liscia
        CurrentNode = CurrentNode->vChildren->at(1); //przechodzimy na ostatnie dziecko aktualnego wezla
    }

    return CurrentNode;
}


cTree& cTree::join(std::vector<std::string> formula) {
    cNode *rightLeaf = findRightLeaf(); //znajdujemy ostatni lisc drzewa z "prawej strony";

    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = rightLeaf; //przypisujemy adres Roota do CurrentNode
    rightLeaf->sValue = formula[0]; //zmieniamy wartosc wezla na ktorym operujemy na wartosc pierwszego elementu formuly

    cNode* newAddedNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres nowego wezla ktory bedziemy dodawac do drzewa

    for (int i = 1; i < formula.size(); i++) { //przechodzimy po formule od drugiego elementu bo pierwszy jest juz w Root
        newAddedNode = new cNode(formula[i]); //przypisujemy adres nowego obiektu cNode z kolejnym elementem formuly ktory bedziemy dodawac do drzewa

        int maxAmountOfChildren = fMaxAmountOfChildren(
                CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora

        if (CurrentNode->vChildren->size() <
            maxAmountOfChildren) { //sprawdzamy czy aktualny wezel ma mniej niz dana ilosc dzieci
            CurrentNode->cAddtoNode(*newAddedNode); //jesli tak to dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (isOperator(newAddedNode->sValue)) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        } else { //jesli aktualny wezel ma juz dopuszczona dzieci to przechodzimy na jego rodzica
            CurrentNode = CurrentNode->cParent;

            maxAmountOfChildren = fMaxAmountOfChildren(
                    CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            while (CurrentNode->vChildren->size() >=
                   maxAmountOfChildren) { //przechodzimy po drzewie az dojdziemy do wezla ktory ma mniej niz dopuszczone ilosc dzieci
                CurrentNode = CurrentNode->cParent;
                maxAmountOfChildren = fMaxAmountOfChildren(
                        CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            }

            CurrentNode->cAddtoNode(*newAddedNode); //dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (isOperator(newAddedNode->sValue)) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        }
    }

    return *this;

}

cTree cTree::join(const cTree& other) {
    cTree newTree(*this); // Create a copy of the current tree
    cNode* rightLeafOther = other.findRightLeaf(); // Find the right leaf of the other tree
    newTree.cRoot = rightLeafOther; // Assign the right leaf of the other tree as the root of the new tree
    return newTree;
}


void cTree::printBTRecursiveHelp(const std::string &prefix, cNode *node, bool isLeft) {
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


void cTree::printBT() const {
    cTree::printBTRecursiveHelp("", cRoot, false); //wywolujemy funkcje rekurencyjna wypisujaca drzewo

}

std::vector<std::string> cTree::getPrefixRecursiveHelp(cNode *node) {
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


std::vector<std::string> cTree::getPrefix() const{
    return getPrefixRecursiveHelp(cRoot); //wywolujemy funkcje rekurencyjna pobierajaca prefiks
}

int cTree::maxDepth(cNode* root) {
    if (!root) return 0; // jeśli nie ma korzenia, to głębokość drzewa wynosi 0

    int maxChildDepth = 0; // głębokość najgłębszego dziecka

    for (cNode* child : *(root->vChildren)) { // dla każdego dziecka korzenia
        int childDepth = cTree::maxDepth(child); // obliczamy głębokość uzywajac rekurencji
        maxChildDepth = std::max(maxChildDepth, childDepth); // i wybieramy największą
    }

    return maxChildDepth + 1; // głębokość korzenia to głębokość najgłębszego dziecka + 1
}

void cTree::getLeavesAtDepth(cNode* node, int currentDepth, int targetDepth, std::vector<cNode*>& leaves) {
    if (!node) return; // jeśli nie ma korzenia, to głębokość drzewa wynosi 0

    if (currentDepth == targetDepth && node->vChildren->empty()) { // jeśli jesteśmy na docelowej głębokości i nie ma dzieci, to dodajemy do wektora
        leaves.push_back(node); // dodajemy do wektora
        return; // i kończymy
    }

    for (cNode* child : *(node->vChildren)) { // dla każdego dziecka korzenia
        cTree::getLeavesAtDepth(child, currentDepth + 1, targetDepth, leaves); // obliczamy głębokość uzywajac rekurencji
    }
}


std::vector<cNode*> cTree::getLeavesAtLowestLevel(cNode* root) {
    std::vector<cNode*> leaves; // wektor liści
    int iMaxDepth = cTree::maxDepth(root); // maksymalna głębokość drzewa

    if (iMaxDepth > 0) { // jeśli drzewo nie jest puste
        cTree::getLeavesAtDepth(root, 0, iMaxDepth - 1, leaves); // pobieramy liście na ostatniej głębokości
    }

    return leaves; // zwracamy wektor liści
}


std::vector<std::vector<cNode*>> cTree::segregateLeavesByParent(const std::vector<cNode*>& leaves) {
    std::vector<std::vector<cNode*>> segregatedLeaves; // wektor wektorów liści

    std::map<cNode*, std::vector<cNode*>> leavesByParent; // mapa liści według rodzica

    // Grupowanie liści według rodzica
    for (const auto& leaf : leaves) { // dla każdego liścia
        if (leaf->cParent != nullptr) { // jeśli liść ma rodzica
            cNode* parent = leaf->cParent; // pobieramy rodzica
            leavesByParent[parent].push_back(leaf); // i dodajemy do mapy
        }
    }

    // Konwersja mapy na wektor wektorów
    for (const auto& pair : leavesByParent) { // dla każdej pary rodzic - liście
        segregatedLeaves.push_back(pair.second); // dodajemy do wektora wektorów
    }

    return segregatedLeaves; // zwracamy wektor wektorów
}


int cTree::compute(std::vector<std::string> formula) const{

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


void cTree::findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables)  const{
    if (currentNode == nullptr) { //sprawdzamy czy wezel nie jest pusty
        return; //jesli tak to konczymy
    }

    if (isVariable(currentNode->sValue) && !isOperator(currentNode->sValue)) { //sprawdzamy czy wartosc wezla jest zmienna i czy nie jest operatorem
        variables.insert(currentNode->sValue); //jesli tak to dodajemy do zbioru zmiennych
    }

    for (cNode* child : *(currentNode->vChildren)) { //przechodzimy po wszystkich dzieciach wezla
        findVariablesRecursive(child, variables); //rekurencyjnie szukamy zmiennych
    }

}


std::set<std::string> cTree::findVariables() const{
    std::set<std::string> variables; //tworzymy set zmiennych
    findVariablesRecursive(cRoot, variables); //rekurencyjnie szukamy zmiennych
    return variables; //zwracamy set zmiennych
}

void cTree::replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables) {
    if (currentNode == nullptr) { //sprawdzamy czy wezel nie jest pusty
        return; //jesli tak to konczymy
    }

    if (currentNode->sValue == variable) { //sprawdzamy czy wartosc wezla jest zmienna
        currentNode->sValue = (replaceValues[std::distance(findVariables.begin(), findVariables.find(variable))]); //jesli tak to zamieniamy na wartosc z wektora wartosci
    }

    for (cNode* child : *currentNode->vChildren) { //przechodzimy po wszystkich dzieciach wezla
        replaceVariableRecursive(child, variable, replaceValues, findVariables); //rekurencyjnie zamieniamy zmienne
    }
}

void cTree::findVariablesAndReplace(std::vector<std::string> replaceValues) {

    std::set<std::string> sFindVariables = findVariables(); //szukamy zmiennych

    for (std::string variable : sFindVariables) { //dla kazdej zmiennej
        replaceVariableRecursive(cRoot, variable, replaceValues, sFindVariables); //rekurencyjnie zamieniamy zmienne
    }
}

