#include "cTree.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>


cTree::cTree(cNode &newRoot) {
    cRoot = &newRoot;
}

cTree::cTree(cTree &other) {
    cRoot = new cNode(*other.cRoot);
}

cTree::cTree() {
    cRoot = nullptr;
}

cTree::~cTree() {
    delete cRoot;
}

cTree enter( std::vector<std::string> formula){
    cNode *Root = new cNode(formula[0]); //tworzymy obiekt cNode z pierwszym elementem formuly jako Root
    cTree *Tree = new cTree(*Root); //tworzymy obiekt cTree z pierwszym elementem formuly jako Root
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = Root; //przypisujemy adres Roota do CurrentNode


    for (int i = 1; i < formula.size(); i++){ //przechodzimy po formule od drugiego elementu bo pierwszy jest juz w Root
        cNode *newAddedNode = new cNode(formula[i]); //tworzymy nowy obiekt cNode z kolejnym elementem formuly ktory bedziemy dodawac w odpowiednie miejsce do drzewa

        int maxAmountOfChildren = fMaxAmountOfChildren(CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora

        if (CurrentNode->vChildren->size() < maxAmountOfChildren) { //sprawdzamy czy aktualny wezel ma mniej niz dana ilosc dzieci
            CurrentNode->cAddtoNode(*newAddedNode); //jesli tak to dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (isOperator(newAddedNode->sValue)) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        }
        else { //jesli aktualny wezel ma juz dopuszczona dzieci to przechodzimy na jego rodzica
            CurrentNode = CurrentNode->CParent;

            maxAmountOfChildren = fMaxAmountOfChildren(CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            while (CurrentNode->vChildren->size() >= maxAmountOfChildren) { //przechodzimy po drzewie az dojdziemy do wezla ktory ma mniej niz dopuszczone ilosc dzieci
                CurrentNode = CurrentNode->CParent;
                maxAmountOfChildren = fMaxAmountOfChildren(CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            }

            CurrentNode->cAddtoNode(*newAddedNode); //dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (newAddedNode->isOperator()) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        }

    }

    return *Tree;

}


cNode* cTree::findRightLeaf() const {
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    while (CurrentNode->vChildren->size() > 1) { //przechodzimy po drzewie az dojdziemy do liscia
        CurrentNode = CurrentNode->vChildren->at(1); //przechodzimy na ostatnie dziecko aktualnego wezla
    }

    return CurrentNode;
}

cNode* cTree::findRightLeaf(cTree &tree) const {
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = tree.cRoot; //przypisujemy adres Roota do CurrentNode
    while (CurrentNode->vChildren->size() > 1) { //przechodzimy po drzewie az dojdziemy do liscia
        CurrentNode = CurrentNode->vChildren->at(1); //przechodzimy na ostatnie dziecko aktualnego wezla
    }

    return CurrentNode;
}


cTree cTree::join( std::vector<std::string> formula) {

    cNode *rightLeaf = findRightLeaf();

    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = rightLeaf; //przypisujemy adres Roota do CurrentNode
    rightLeaf->sValue = formula[0]; //zmieniamy wartosc wezla na ktorym operujemy na wartosc pierwszego elementu formuly


    for (int i = 1; i < formula.size(); i++) { //przechodzimy po formule od drugiego elementu bo pierwszy jest juz w Root
        cNode *newAddedNode = new cNode(formula[i]); //tworzymy nowy obiekt cNode z kolejnym elementem formuly ktory bedziemy dodawac w odpowiednie miejsce do drzewa

        int maxAmountOfChildren = fMaxAmountOfChildren(
                CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora

        if (CurrentNode->vChildren->size() <
            maxAmountOfChildren) { //sprawdzamy czy aktualny wezel ma mniej niz dana ilosc dzieci
            CurrentNode->cAddtoNode(*newAddedNode); //jesli tak to dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (isOperator(newAddedNode->sValue)) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        } else { //jesli aktualny wezel ma juz dopuszczona dzieci to przechodzimy na jego rodzica
            CurrentNode = CurrentNode->CParent;

            maxAmountOfChildren = fMaxAmountOfChildren(
                    CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            while (CurrentNode->vChildren->size() >=
                   maxAmountOfChildren) { //przechodzimy po drzewie az dojdziemy do wezla ktory ma mniej niz dopuszczone ilosc dzieci
                CurrentNode = CurrentNode->CParent;
                maxAmountOfChildren = fMaxAmountOfChildren(
                        CurrentNode->sValue); //zmienna przechowujaca maksymalna ilosc dzieci dla danego rodzaju operatora
            }

            CurrentNode->cAddtoNode(*newAddedNode); //dodajemy nowy wezel do aktualnego wezla na ktorym operujemy
            if (newAddedNode->isOperator()) {   //jesli nowy wezel jest operatorem to przechodzimy na niego
                CurrentNode = newAddedNode; //przypisujemy adres nowego wezla do CurrentNode
            }
        }
    }

    return *this;
}

cTree cTree::join(cTree &other) {

    cTree *finalTree = new cTree(*this);
    cTree *otherTree = new cTree(other);

    cNode *rightLeaf = findRightLeaf(*finalTree);

    *rightLeaf = *otherTree->cRoot;

    return *finalTree;
}


void printBT(const std::string &prefix, cNode *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "`--");

        // print the value of the node
        std::cout << node->sValue << std::endl;

        // print children
        if (node->vChildren != nullptr && !node->vChildren->empty()) {
            for (size_t i = 0; i < node->vChildren->size(); ++i) {
                printBT(prefix + (isLeft ? "|   " : "    "), (*node->vChildren)[i],
                        i < node->vChildren->size() - 1);
            }
        }
    }
}


void printBT(cNode *node) {
    if (node != nullptr) printBT("", node, false);

}


int maxDepth(cNode* node) {
    if (!node)
        return 0;

    int leftDepth = maxDepth(node->vChildren->size() > 0 ? node->vChildren->at(0) : nullptr);
    int rightDepth = maxDepth(node->vChildren->size() > 1 ? node->vChildren->at(1) : nullptr);

    return std::max(leftDepth, rightDepth) + 1;
}


void getLeavesAtDepth(cNode* node, int currentDepth, int targetDepth, std::vector<cNode*>& leaves) {
    if (!node)
        return;

    if (currentDepth == targetDepth && node->vChildren->empty()) {
        leaves.push_back(node);
        return;
    }

    for (cNode* child : *(node->vChildren)) {
        getLeavesAtDepth(child, currentDepth + 1, targetDepth, leaves);
    }
}


std::vector<cNode*> getLeavesAtLowestLevel(cNode* root) {
    std::vector<cNode*> leaves;
    int iMaxDepth = maxDepth(root);

    if (iMaxDepth > 0) {
        getLeavesAtDepth(root, 0, iMaxDepth - 1, leaves); // targetDepth = maxDepth - 1
    }

    return leaves;
}


std::vector<std::vector<cNode*>> segregateLeavesByParent(const std::vector<cNode*>& leaves) {
    std::vector<std::vector<cNode*>> segregatedLeaves;

    std::map<cNode*, std::vector<cNode*>> leavesByParent;

    // Grupowanie liści według rodzica
    for (const auto& leaf : leaves) {
        if (leaf->CParent != nullptr) {
            cNode* parent = leaf->CParent;
            leavesByParent[parent].push_back(leaf);
        }
    }

    // Konwersja mapy na wektor wektorów
    for (const auto& pair : leavesByParent) {
        segregatedLeaves.push_back(pair.second);
    }

    return segregatedLeaves;
}


int cTree::compute( std::vector<std::string> formula){

    cTree *Tree = new cTree(*this);

    Tree->findVariablesAndReplace(formula);


    while (Tree->cRoot != nullptr) {

        std::vector<cNode *> leaves = getLeavesAtLowestLevel(Tree->cRoot);
        std::vector<std::vector<cNode *>> segregatedLeaves = segregateLeavesByParent(leaves);

        for (const auto &leaves: segregatedLeaves) {
            int newValue = (leaves[0]->CParent->sValue == "*") ? 1 : 0;

            for (const auto &leaf: leaves) {
                std::string parentOperator = leaf->CParent->sValue;

                //TODO zmienic na zmienna stoi jakby int czaisz

                if (parentOperator == "+") {
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

            if (leaves[0]->CParent->CParent == nullptr) {
                delete Tree;
                return newValue;
            }

            leaves[0]->CParent->sValue = std::to_string(newValue);


            for (const auto &leaf: leaves) delete leaf;
        }
    }
    return -1;

}

cTree& cTree::operator=(const cTree& other) {
    if (this != &other) {
        delete cRoot;
        cRoot = new cNode(*other.cRoot);
    }
    return *this;
}

cTree cTree::operator+(cTree& other){

    return join(other);
}


void cTree::findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables)  {
    if (currentNode == nullptr) {
        return;
    }

    // Check if the current node's value is a variable
    if (!currentNode->isOperator() && checkIfVariable(currentNode->sValue)) {
        variables.insert(currentNode->sValue);
    }

    // Recursively visit children
    if (currentNode->vChildren != nullptr) {
        for (cNode* child : *(currentNode->vChildren)) {
            findVariablesRecursive(child, variables);
        }
    }
}

std::set<std::string> cTree::findVariables() {
    std::set<std::string> variables;
    findVariablesRecursive(cRoot, variables);
    return variables;
}

void cTree::replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables) {
    if (currentNode == nullptr) {
        return;
    }

    if (currentNode->sValue == variable) {
        currentNode->setValue(replaceValues[std::distance(findVariables.begin(), findVariables.find(variable))]);
    }

    // Recursively visit children
    for (cNode* child : *currentNode->vChildren) {
        replaceVariableRecursive(child, variable, replaceValues, findVariables);
    }
}

void cTree::findVariablesAndReplace(std::vector<std::string> replaceValues) {

    std::set<std::string> sFindVariables = findVariables();

    for (std::string variable : sFindVariables) {
        replaceVariableRecursive(cRoot, variable, replaceValues, sFindVariables);
    }
}

