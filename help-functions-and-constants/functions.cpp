#include "functions.h"

bool isOperator(const std::string& sValue) {
    for(const auto & i : OPERATORS) {
        if (sValue == i) {
            return true;
        }
    }
    return false;
}

bool isArthOperator(const std::string& sValue) {
    for(const auto & i : ARTH_OPERATORS) {
        if (sValue == i) {
            return true;
        }
    }
    return false;
}

bool isTrigOperator(const std::string& sValue) {
    for(const auto & i : TRIG_OPERATORS) {
        if (sValue == i) {
            return true;
        }
    }
    return false;
}

int fMaxAmountOfChildren(const std::string& sValue) {
    if (isArthOperator(sValue)) {
        return MAX_AMOUNT_OF_CHILDREN_FOR_ARTH;
    } else if (isTrigOperator(sValue)) {
        return MAX_AMOUNT_OF_CHILDREN_FOR_TRIG;
    } else {
        return 0;
    }
}


std::vector<std::string> format(const std::string& sFormula) {
    std::vector<std::string> vFormula;
    std::string sTemp;
    for (char c : sFormula) {
        if (c == ' ') {
            if (!sTemp.empty()) {
                vFormula.push_back(sTemp);
                sTemp = "";
            }
        } else if (isOperator(std::string(1, c))) {
            if (!sTemp.empty()) {
                vFormula.push_back(sTemp);
                sTemp = "";
            }
            vFormula.push_back(std::string(1, c));
        } else {
            sTemp += c;
        }
    }
    if (!sTemp.empty()) {
        vFormula.push_back(sTemp);
    }
    return vFormula;
}

bool checkIfOnlyNumbers(const std::vector<std::string>& formula) {

    for (const std::string &str: formula) if (!checkIfNumber(str)) return false;

    return true;
}

bool checkIfNumber(std::string sValue) {
    for (char c: sValue) {
        if (!isdigit(c) || (sValue[0] == '0' && sValue.size() > 1)) {
            return false;
        }
    }
    return true;
}

bool checkIfVariable(std::string sValue) {
    if (isalpha(sValue[0])) return true;
    return false;
}

bool checkIfPN(std::vector<std::string> formula) {
    std::stack<int> s;
    for (auto token = formula.rbegin(); token != formula.rend(); ++token) {
        if (isArthOperator(*token)) {
            if (s.size() < 2) return false;
            s.pop();

        } else if (isTrigOperator(*token)) {
            if (s.empty()) return false;

        } else if (checkIfNumber(*token) || checkIfVariable(*token)) {
            s.push(1);

        } else {
            return false;
        }
    }
    return s.size() == 1;
}
