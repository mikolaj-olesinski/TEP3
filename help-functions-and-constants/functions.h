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

bool isPN(const std::vector<std::string>& formula); // sprawdza czy podana formula jest poprawna notacja polska
bool checkIfOnlyNumbers(const std::vector<std::string>& formula); // sprawdza czy wszystkie elementy wektora sa liczbami
bool isNumber(const std::string& sValue); // sprawdza czy string jest liczba
bool isVariable(const std::string& sValue); // sprawdza czy string jest zmienna
bool isStringVariable(const std::string& sValue); // sprawdza czy string jest zmienna typu string
bool isString(const std::string& sValue); // sprawdza czy string jest stringiem

std::string addString(const std::string& string1, const std::string& string2); // dodaje dwa stringi
std::string subString(const std::string& string1, const std::string& string2); // odejmuje dwa stringi
std::string mulString(const std::string& string1, const std::string& string2); // mnozy dwa stringi
std::string divString(const std::string& string1, const std::string& string2); // dzieli dwa stringi

std::vector<std::string> format(const std::string& sFormula); // formatuje stringa do wektora stringow
void UI(); // funkcja interfejsu uzytkownika

#endif

