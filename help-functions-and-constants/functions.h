#ifndef TEP3_FUNCTIONS_H
#define TEP3_FUNCTIONS_H

#include <string>
#include <vector>
#include <stack>
#include "../help-functions-and-constants/stale.h"

bool isOperator(const std::string& sValue); // sprawdza czy string jest operatorem
bool isArthOperator(const std::string& sValue);  // sprawdza czy string jest operatorem arytmetycznym
bool isTrigOperator(const std::string& sValue); // sprawdza czy string jest operatorem trygonometrycznym
int fMaxAmountOfChildren(const std::string& sValue); // zwraca maksymalna ilosc dzieci dla danego operatora

bool isPN(std::vector<std::string> formula); // sprawdza czy podana formula jest poprawna notacja polska
bool checkIfOnlyNumbers(const std::vector<std::string>& formula); // sprawdza czy wszystkie elementy wektora sa liczbami
bool isNumber(std::string sValue); // sprawdza czy string jest liczba
bool isVariable(std::string sValue); // sprawdza czy string jest zmienna


std::vector<std::string> format(const std::string& sFormula); // formatuje stringa do wektora stringow
void UI(); // funkcja interfejsu uzytkownika

#endif

