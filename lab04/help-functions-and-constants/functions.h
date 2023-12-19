#ifndef TEP3_FUNCTIONS_H
#define TEP3_FUNCTIONS_H

#include <string>
#include <vector>
#include <stack>
#include <set>
#include "stale.h"

bool isOperator(const std::string& sValue); // sprawdza czy string jest operatorem
bool isArthOperator(const std::string& sValue);  // sprawdza czy string jest operatorem arytmetycznym
bool isTrigOperator(const std::string& sValue); // sprawdza czy string jest operatorem trygonometrycznym
int fMaxAmountOfChildren(const std::string& sValue); // zwraca maksymalna ilosc dzieci dla danego operatora

bool isPN(std::vector<std::string>& formula); // sprawdza czy podana formula jest poprawna notacja polska

bool isVariable(std::string sValue); // sprawdza czy string jest zmienna
bool isStringVariable(std::string sValue); // sprawdza czy string jest zmienna typu string
bool isString(const std::string& sValue); // sprawdza czy string jest stringiem
bool isInt(const std::string& sValue); // sprawdza czy string jest intem
bool isDouble(const std::string& sValue); // sprawdza czy string jest doublem

std::set<int> positionsOfPattern(const std::string& sFormula, const std::string& sPattern); // zwraca pozycje wzorca w stringu
std::string addString(const std::string& string1, const std::string& string2); // dodaje dwa stringi
std::string subString(const std::string& string1, const std::string& string2); // odejmuje dwa stringi
std::string mulString(const std::string& string1, const std::string& string2); // mnozy dwa stringi
std::string divString(const std::string& string1, const std::string& string2); // dzieli dwa stringi

std::vector<std::string> format(const std::string& sFormula); // formatuje stringa do wektora stringow

#endif

