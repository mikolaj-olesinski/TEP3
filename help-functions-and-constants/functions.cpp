#include <stack>
#include "functions.h"

bool isOperator(std::string sValue) {
    for(int i = 0; i < OPERATORS_SIZE; i++) {
        if (sValue == OPERATORS[i]) {
            return true;
        }
    }
    return false;
}

bool isArthOperator(std::string sValue) {
    for(int i = 0; i < ARTH_OPERATORS_SIZE; i++) {
        if (sValue == ARTH_OPERATORS[i]) {
            return true;
        }
    }
    return false;
}

bool isTrigOperator(std::string sValue) {
    for(int i = 0; i < TRIG_OPERATORS_SIZE; i++) {
        if (sValue == TRIG_OPERATORS[i]) {
            return true;
        }
    }
    return false;
}

int fMaxAmountOfChildren(std::string sValue) {
    if (isArthOperator(sValue)) {
        return MAX_AMOUNT_OF_CHILDREN_FOR_ARTH;
    } else if (isTrigOperator(sValue)) {
        return MAX_AMOUNT_OF_CHILDREN_FOR_TRIG;
    } else {
        return 0;
    }
}

bool check(std::string sFormula) {
    //TODO zrobic
    return true;
}

std::vector<std::string> format(std::string sFormula) {
    std::vector<std::string> vFormula;
    std::string sTemp = "";
    for (char c : sFormula) {
        if (c == ' ') {
            if (sTemp != "") {
                vFormula.push_back(sTemp);
                sTemp = "";
            }
        } else if (isOperator(std::string(1, c))) {
            if (sTemp != "") {
                vFormula.push_back(sTemp);
                sTemp = "";
            }
            vFormula.push_back(std::string(1, c));
        } else {
            sTemp += c;
        }
    }
    if (sTemp != "") {
        vFormula.push_back(sTemp);
    }
    return vFormula;
}

bool checkIfOnlyNumbers(const std::vector<std::string> formula) {

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
            if (s.size() < 1) return false;

        } else if (checkIfNumber(*token) || checkIfVariable(*token)) {
            s.push(1);

        } else {
            return false;
        }
    }
    return s.size() == 1;
}
