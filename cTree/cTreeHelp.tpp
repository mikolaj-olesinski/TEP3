#include "cTree.h"

template <typename T>
T cTree<T>::computeNode(cNode* node, const std::vector<std::string> valuesOfVariables) const {

    if (isVariable(node->sValue)) {
        auto variables = findVariables();
        return std::stod(valuesOfVariables[std::distance(variables.begin(), variables.find(node->sValue))]);
    } else if (!isOperator(node->sValue)) {
        return std::stod(node->sValue); // Jeśli węzeł nie jest operatorem, zwróć jego wartość
    } else { // Jeśli węzeł jest operatorem, oblicz wartość na podstawie wartości jego dzieci
        std::string parentOperator = node->sValue; //przypisujemy operator do zmiennej

        if(isTrigOperator(parentOperator)){ //sprawdzamy czy operator jest funkcja trygonometryczna
            T leftValue = computeNode((*node->vChildren)[0], valuesOfVariables); //obliczamy wartosc dziecka
            if (parentOperator == "sin") { //sprawdzamy jaka funkcja trygonometryczna
                return std::sin(leftValue); //obliczamy wartosc funkcji
            } else if (parentOperator == "cos") { //sprawdzamy jaka funkcja trygonometryczna
                return std::cos(leftValue); //obliczamy wartosc funkcji
            }
        }
        else if(isArthOperator(parentOperator)){ //sprawdzamy czy operator jest operatorem arytmetycznym
            T leftValue = computeNode((*node->vChildren)[0], valuesOfVariables); //obliczamy wartosc lewego dziecka
            T rightValue = computeNode((*node->vChildren)[1], valuesOfVariables); //obliczamy wartosc prawego dziecka

            if (parentOperator == "+") { //sprawdzamy jaki operator arytmetyczny
                return leftValue + rightValue; //obliczamy wartosc wyrazenia
            } else if (parentOperator == "*") {
                return leftValue * rightValue;
            } else if (parentOperator == "-") {
                return leftValue - rightValue;
            } else if (parentOperator == "/") {
                if (rightValue == 0) throw std::invalid_argument("nie dziel przez 0"); //sprawdzamy czy nie dzielimy przez 0
                else return leftValue / rightValue;
            }
        }
    }
    return -1; //zwracamy -1 jesli nie udalo sie obliczyc wartosci
}


template <>
std::string cTree<std::string>::computeNode(cNode* node, const std::vector<std::string> valuesOfVariables) const { //specjalizacja dla stringow
    if (isStringVariable(node->sValue)) { //sprawdzamy czy wartosc wezla jest zmienna dla stringow
        auto variables = findVariables();
        return (valuesOfVariables[std::distance(variables.begin(), variables.find(node->sValue))]);    }
    else if (!isOperator(node->sValue)) {
        return node->sValue; // Jeśli węzeł nie jest operatorem, zwróć jego wartość
    } else { // Jeśli węzeł jest operatorem, oblicz wartość na podstawie wartości jego dzieci
        std::string parentOperator = node->sValue;

        if(isArthOperator(parentOperator)){ //sprawdzamy czy operator jest operatorem arytmetycznym
            std::string leftValue = computeNode((*node->vChildren)[0], valuesOfVariables); //obliczamy wartosc lewego dziecka
            std::string rightValue = computeNode((*node->vChildren)[1], valuesOfVariables); //obliczamy wartosc prawego dziecka

            if (parentOperator == "+") { //sprawdzamy jaki operator arytmetyczny
                return addString(leftValue, rightValue); //obliczamy wartosc wyrazenia uzywajac specjlalnych fu
            } else if (parentOperator == "*") {
                return mulString(leftValue, rightValue);
            } else if (parentOperator == "-") {
                return subString(leftValue, rightValue);
            } else if (parentOperator == "/") {
                return divString(leftValue, rightValue);
            }
        }
    }
    return ""; //zwracamy pusty string jesli nie udalo sie obliczyc wartosci
}






template <typename T>
cNode* cTree<T>::findRightLeafParent() const {
    cNode *CurrentNode; //tworzymy wskaznik na obiekt cNode w ktroym bedziemy przechowywac adres aktualnego wezla na ktorym dzialamy
    CurrentNode = cRoot; //przypisujemy adres Roota do CurrentNode
    while (CurrentNode->vChildren->size() != 0) { //przechodzimy po drzewie az dojdziemy do liscia
        CurrentNode = CurrentNode->vChildren->back(); //przechodzimy na ostatnie dziecko
    }
    return CurrentNode->cParent; //zwracamy rodzica liscia
}


template <typename T>
void cTree<T>::findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables){
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

template <>
void cTree<std::string>::findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables){
    if (currentNode == nullptr) { //sprawdzamy czy wezel nie jest pusty
        return; //jesli tak to konczymy
    }

    if (isStringVariable(currentNode->sValue) && !isOperator(currentNode->sValue)) { //sprawdzamy czy wartosc wezla jest zmienna i czy nie jest operatorem
        variables.insert(currentNode->sValue); //jesli tak to dodajemy do zbioru zmiennych
    }

    for (cNode* child : *(currentNode->vChildren)) { //przechodzimy po wszystkich dzieciach wezla
        findVariablesRecursive(child, variables); //rekurencyjnie szukamy zmiennych
    }

}


template <typename T>
void cTree<T>::replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables){
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


template <typename T>
int cTree<T>::maxDepth(cNode* root) {
    if (!root) return 0; // jeśli nie ma korzenia, to głębokość drzewa wynosi 0

    int maxChildDepth = 0; // głębokość najgłębszego dziecka

    for (cNode* child : *(root->vChildren)) { // dla każdego dziecka korzenia
        int childDepth = cTree::maxDepth(child); // obliczamy głębokość uzywajac rekurencji
        maxChildDepth = std::max(maxChildDepth, childDepth); // i wybieramy największą
    }

    return maxChildDepth + 1; // głębokość korzenia to głębokość najgłębszego dziecka + 1
}


template <typename T>
void cTree<T>::getLeavesAtDepth(cNode* node, int currentDepth, int targetDepth, std::vector<cNode*>& leaves) {
    if (!node) return; // jeśli nie ma korzenia, to głębokość drzewa wynosi 0

    if (currentDepth == targetDepth && node->vChildren->empty()) { // jeśli jesteśmy na docelowej głębokości i nie ma dzieci, to dodajemy do wektora
        leaves.push_back(node); // dodajemy do wektora
        return; // i kończymy
    }

    for (cNode* child : *(node->vChildren)) { // dla każdego dziecka korzenia
        cTree::getLeavesAtDepth(child, currentDepth + 1, targetDepth, leaves); // obliczamy głębokość uzywajac rekurencji
    }
}


template <typename T>
void cTree<T>::printBTRecursiveHelp(const std::string &prefix, cNode *node, bool isLeft) {
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
std::vector<std::string> cTree<T>::getPrefixRecursiveHelp(cNode *node) {
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

