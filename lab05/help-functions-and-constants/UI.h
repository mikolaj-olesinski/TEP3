#include <iostream>
#include <string>
#include <sstream>
#include "../cTree/cTree.h"
#include "../cTree/cTreeHelp.tpp"
#include "../cTree/cTree.tpp"

template <typename>
class UI {
public:
    void run(); // uruchomienie UI z odpowiednim typem drzewa
private:
    void printHelp(); // wypisanie pomocy dla uzytkownika
    bool checkFormulaWithVariables(std::vector<std::string> formula); // sprawdza czy formuła jest poprawna (formula moze byc ze zmiennymi)
    bool checkFormula(std::vector<std::string> formula); // sprawdza czy formuła jest poprawna (formula musi byc bez zmiennych)
};

void startUIAndDetermineTypeOfTree(); // uruchomienie UI i wybranie typu drzewa

#ifndef TEP3_UI_H
#define TEP3_UI_H

#endif //TEP3_UI_H
