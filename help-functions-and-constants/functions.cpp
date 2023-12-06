#include "functions.h"

bool isOperator(const std::string& sValue) {
    for(const auto & i : OPERATORS) { //dla kazdego elementu z OPERATORS
        if (sValue == i) { //jesli element z OPERATORS jest rowny sValue
            return true; //zwroc true
        }
    }
    return false; //jesli nie zwroc false
}

bool isArthOperator(const std::string& sValue) {
    for(const auto & i : ARTH_OPERATORS) { //dla kazdego elementu z OPERATORS
        if (sValue == i) { //jesli element z OPERATORS jest rowny sValue
            return true; //zwroc true
        }
    }
    return false; //jesli nie zwroc false
}

bool isTrigOperator(const std::string& sValue) { //dla kazdego elementu z OPERATORS
    for(const auto & i : TRIG_OPERATORS) { //jesli element z OPERATORS jest rowny sValue
        if (sValue == i) { //zwroc true
            return true; //jesli nie zwroc false
        }
    }
    return false; //jesli nie zwroc false
}

int fMaxAmountOfChildren(const std::string& sValue) {
    if (isArthOperator(sValue)) { //jesli string jest operatorem arytmetycznym
        return MAX_AMOUNT_OF_CHILDREN_FOR_ARTH; //zwroc maksymalna ilosc dzieci dla operatora arytmetycznego
    } else if (isTrigOperator(sValue)) { //jesli string jest operatorem trygonometrycznym
        return MAX_AMOUNT_OF_CHILDREN_FOR_TRIG;
    } else {
        return 0; //jesli nie zwroc 0
    }
}


std::vector<std::string> format(const std::string& sFormula) {
    std::vector<std::string> vFormula; //wektor stringow
    std::string sTemp; //tymczasowy string
    for (char c : sFormula) { //dla kazdego znaku w stringu
        if (c == ' ') { //jesli znak jest spacja
            if (!sTemp.empty()) { //jesli string nie jest pusty
                vFormula.push_back(sTemp); //dodaj string do wektora
                sTemp = ""; //wyczysc string
            }
        } else if (isOperator(std::string(1, c))) { //jesli znak jest operatorem
            if (!sTemp.empty()) { //jesli string nie jest pusty
                vFormula.push_back(sTemp); //dodaj string do wektora
                sTemp = ""; //wyczysc string
            }
            vFormula.push_back(std::string(1, c)); //dodaj operator do wektora
        } else {
            sTemp += c; //dodaj znak do stringu
        }
    }
    if (!sTemp.empty()) { //jesli string nie jest pusty
        vFormula.push_back(sTemp); //dodaj string do wektora
    }
    return vFormula; //zwroc wektor
}

bool checkIfOnlyNumbers(const std::vector<std::string>& formula) {

    for (const std::string &str: formula) if (!isNumber(str)) return false; //jesli string nie jest liczba zwroc false

    return true; //jesli wszystkie stringi sa liczbami zwroc true
}

bool isNumber(const std::string& sValue) {
    if (sValue.empty()) {
        return false; // Pusty string nie jest liczbą
    }

    bool hasDot = false; // Flaga wskazująca, czy pojawiła się kropka
    bool hasMinusSign = false; // Flaga wskazująca, czy pojawił się znak minus

    for (size_t i = 0; i < sValue.size(); ++i) {
        char c = sValue[i];

        if (i == 0 && c == '-') {
            // Pierwszy znak to minus, ustawiamy flagę hasMinusSign
            hasMinusSign = true;
        } else if (!std::isdigit(c)) {
            // Jeśli znak nie jest cyfrą
            if (c == '.' && !hasDot) {
                // Jeśli to kropka i jeszcze jej nie było, to jest to akceptowalne
                hasDot = true;
            } else {
                return false; // Inny niż cyfra i nieakceptowalna kropka
            }
        }
    }

    // Jeśli był znak minus i string ma tylko jeden znak, to nie jest poprawna liczba
    if (hasMinusSign && sValue.size() == 1) {
        return false;
    }

    return true;
}



bool isVariable(const std::string& sValue) {
    if (isalpha(sValue[0])) return true; //jesli pierwszy znak jest litera zwroc true
    return false; //jesli nie zwroc false
}

bool isPN(const std::vector<std::string>& formula) {
    std::stack<int> s; //stos intow
    for (auto token = formula.rbegin(); token != formula.rend(); ++token) { //dla kazdego elementu wektora od konca
        if (isArthOperator(*token)) { //jesli element jest operatorem arytmetycznym
            if (s.size() < 2) return false; //jesli stos ma mniej niz 2 elementy zwroc false
            s.pop(); //usun element ze stosu

        } else if (isTrigOperator(*token)) { //jesli element jest operatorem trygonometrycznym
            if (s.empty()) return false; //jesli stos jest pusty zwroc false

        } else if (isNumber(*token) || isVariable(*token)) { //jesli element jest liczba lub zmienna
            s.push(1); //dodaj 1 na stos

        } else { //jesli element nie jest ani operatorem ani liczba ani zmienna
            return false; //zwroc false
        }
    }
    return s.size() == 1; //jesli stos ma 1 element zwroc true
}
//sprawdza czy pierwszy i ostatni znak jest cudzyslowiem a w srodku sa tylko litery
bool isStringVariable(const std::string& sValue) {
    if (sValue[0] == '"' && sValue[sValue.length() - 1] == '"') { //jesli pierwszy i ostatni znak jest cudzyslowiem
        for (int i = 1; i < sValue.length() - 1; i++) { //dla kazdego znaku w stringu
            if (!isalpha(sValue[i])) { //jesli znak nie jest litera
                return false; //zwroc false
            }
        }
        return true; //jesli wszystkie znaki sa literami zwroc true
    }
    return false; //jesli pierwszy i ostatni znak nie jest cudzyslowiem zwroc false
}

bool isString(const std::string& sValue) {
    if (isOperator(sValue)) return false; //jesli string jest operatorem zwroc false
    for (char c : sValue) { //dla kazdego znaku w stringu
        if (!isalpha(c)) { //jesli znak nie jest litera
            return false; //zwroc false
        }
    }
    return true; //jesli wszystkie znaki sa literami zwroc true
}


std::string subString(const std::string& string1, const std::string& string2) {
    std::string result = string1;
    size_t pos = result.rfind(string2);
    if (pos != std::string::npos) {
        result.erase(pos, string2.length());
    }
    return result;
}

std::string addString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}


std::string mulString(const std::string& string1, const std::string& string2) { //TODO do poprawy
    if (string2.empty()) {
        return string1;
    }

    std::string result = string1;
    size_t pos = result.find(string2[0]);

    while (pos != std::string::npos) {
        result.replace(pos, 1, string2.substr(1));
        pos = result.find(string2[0], pos + string2.length() - 1 + 1);
    }

    return result;
}

std::string divString(const std::string& string1, const std::string& string2) {
    std::string result = string1;
    size_t pos = result.rfind(string2);
    if (pos != std::string::npos) {
        result.erase(pos, string2.length());
    }
    return result;
}
