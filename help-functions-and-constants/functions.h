#ifndef TEP3_FUNCTIONS_H
#define TEP3_FUNCTIONS_H

#include <string>
#include <vector>
#include <stack>
#include "../help-functions-and-constants/stale.h"

bool isOperator(const std::string& sValue);
bool isArthOperator(const std::string& sValue);
bool isTrigOperator(const std::string& sValue);
int fMaxAmountOfChildren(const std::string& sValue);

bool checkIfPN(std::vector<std::string> formula);
bool checkIfOnlyNumbers(const std::vector<std::string>& formula);
bool checkIfNumber(std::string sValue);
bool checkIfVariable(std::string sValue);


std::vector<std::string> format(const std::string& sFormula);
void UI();

#endif
