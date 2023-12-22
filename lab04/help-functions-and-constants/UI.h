#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "../cTree/cTree.h"
#include "../cTree/cTreeHelp.tpp"
#include "../cTree/cTree.tpp"


template <typename T>
class UI {
public:
    void run(); // uruchomienie UI z odpowiednim typem drzewa
private:
    void printHelp(); // wypisanie pomocy dla uzytkownika
    bool checkFormulaWithVariables(std::vector<std::string>& formula); // sprawdza czy formuła jest poprawna (formula moze byc ze zmiennymi)
    bool checkFormula(std::vector<std::string>& formula); // sprawdza czy formuła jest poprawna (formula musi byc bez zmiennych)

    void handleEnter(cTree<T> &Tree, std::string &rest); // obsluga komendy enter
    void handlePrintTree(cTree<T> &Tree); // obsluga komendy printTree
    void handlePrint(cTree<T> &Tree); // obsluga komendy print
    void handleComp(cTree<T> &Tree, std::string &rest); // obsluga komendy comp
    void handleJoin(cTree<T> &Tree, std::string &rest); // obsluga komendy join
    void handleVars(cTree<T> &Tree); // obsluga komendy vars
    void handleReset(); // obsluga komendy reset


};

void startUIAndDetermineTypeOfTree(); // uruchomienie UI i wybranie typu drzewa

enum Command { // mozliwe komendy
    ENTER,
    PRINT_TREE,
    PRINT,
    COMP,
    JOIN,
    VARS,
    RESET,
    EXIT,
    UNKNOWN
};

Command convertToCommand(const std::string& str) { // konwersja stringa na komende
    if (str == "enter") return ENTER;
    else if (str == "printTree") return PRINT_TREE;
    else if (str == "print") return PRINT;
    else if (str == "comp") return COMP;
    else if (str == "join") return JOIN;
    else if (str == "vars") return VARS;
    else if (str == "reset") return RESET;
    else if (str == "exit") return EXIT;
    else return UNKNOWN;
}

