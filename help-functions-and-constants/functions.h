#ifndef TEP3_FUNCTIONS_H
#define TEP3_FUNCTIONS_H

#include <string>
#include <vector>
#include "../help-functions-and-constants/stale.h"

bool isOperator(std::string sValue);
bool isArthOperator(std::string sValue);
bool isTrigOperator(std::string sValue);
int fMaxAmountOfChildren(std::string sValue);

bool checkIfPN(std::vector<std::string> formula);
bool checkIfOnlyNumbers(std::vector<std::string> formula);
bool checkIfNumber(std::string sValue);
bool checkIfVariable(std::string sValue);


std::vector<std::string> format(std::string sFormula);
void UI();

#endif
