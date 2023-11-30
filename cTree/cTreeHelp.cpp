#include "cTree.h"

cNode* cTree::findRightLeafParent() const {
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    while (CurrentNode->vChildren->size() != 0) { //przechodzimy po drzewie az dojdziemy do liscia
        CurrentNode = CurrentNode->vChildren->back(); //przechodzimy na ostatnie dziecko
    }
    return CurrentNode->cParent; //zwracamy rodzica liscia
}


void cTree::findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables){
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


void cTree::replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables){
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

