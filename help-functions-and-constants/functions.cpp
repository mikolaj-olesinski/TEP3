#include <sstream>
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
    std::vector<std::string> vFormula; //wektor stringow vFormula
    std::istringstream iss(sFormula); //string stream z sFormula
    std::string word; //string w ktorym bedzie przechowywany pojedynczy wyraz

    while (iss >> word) { //dopoki w string streamie jest cos do pobrania
        vFormula.push_back(word); //dodaj wyraz do wektora
    }

    return vFormula; //zwroc wektor
}


bool isInt(const std::string sValue) {
    if (sValue.empty()) {
        return false; // Pusty string nie jest liczbą całkowitą
    }

    for (size_t i = 0; i < sValue.size(); ++i) {
        char c = sValue[i];

        if (i == 0 && c == '-') {
            // Pierwszy znak to minus, akceptowalne dla liczb ujemnych
            continue;
        }

        if (!std::isdigit(c)) {
            return false; // Jeśli znak nie jest cyfrą
        }
    }

    return true;
}

bool isDouble(const std::string sValue) {
    if (sValue.empty()) {
        return false; // Pusty string nie jest liczbą zmiennoprzecinkową
    }

    bool hasDot = false; // Flaga wskazująca, czy pojawiła się kropka

    for (size_t i = 0; i < sValue.size(); ++i) {
        char c = sValue[i];

        if (i == 0 && c == '-') {
            // Pierwszy znak to minus, akceptowalne dla liczb ujemnych
            continue;
        }

        if (sValue[0] == '0' && sValue.size() > 1) {
            // Jeśli pierwszy znak to '0', a string ma więcej niż jeden znak, to jest niepoprawne
            return false;
        }

        if (!std::isdigit(c)) {
            // Jeśli znak nie jest cyfrą
            if (c == '.' && !hasDot) {
                // Jeśli to kropka i jeszcze jej nie było, to jest to akceptowalne
                hasDot = true;
            } else {
                return false; // Inny niż cyfra i nieakceptowalna kropka
            }
        }
    }

    return true;
}


bool isVariable(std::string sValue) {
    if (isalpha(sValue[0])) return true; //jesli pierwszy znak jest litera zwroc true
    return false; //jesli nie zwroc false
}

bool isPN(std::vector<std::string> formula) { //
    std::stack<int> s; //stos intow
    for (auto token = formula.rbegin(); token != formula.rend(); ++token) { //dla kazdego elementu wektora od konca
        if (isArthOperator(*token)) { //jesli element jest operatorem arytmetycznym
            if (s.size() < 2) return false; //jesli stos ma mniej niz 2 elementy zwroc false
            s.pop(); //usun element ze stosu

        } else if (isTrigOperator(*token)) { //jesli element jest operatorem trygonometrycznym
            if (s.empty()) return false; //jesli stos jest pusty zwroc false

        } else s.push(1); //jesli element nie jest operatorem dodaj 1 do stosu
    }
    return s.size() == 1; //jesli stos ma 1 element zwroc true
}
//sprawdza czy pierwszy i ostatni znak jest cudzyslowiem a w srodku sa tylko litery

bool isStringVariable(std::string sValue) {
    if (sValue[0] == '"' && sValue[sValue.length() - 1] == '"') { //jesli pierwszy i ostatni znak jest cudzyslowiem
        for (int i = 1; i < sValue.length() - 1; i++) { //dla kazdego znaku w stringu
            if (!isalpha(sValue[i]) && !isdigit(sValue[i])) { //jesli znak nie jest litera i nie jest cyfra
                return false; //zwroc false
            }
        }
        return true; //jesli wszystkie znaki sa literami zwroc true
    }
    return false; //jesli pierwszy i ostatni znak nie jest cudzyslowiem zwroc false
}

bool isString(std::string sValue) {
    if (isOperator(sValue)) return false; //jesli string jest operatorem zwroc false
    for (char c : sValue) { //dla kazdego znaku w stringu
        if (!isalpha(c) && !isdigit(c)) { //jesli znak nie jest litera i nie jest cyfra
            return false; //zwroc false
        }
    }
    return true; //jesli wszystkie znaki sa literami zwroc true
}

std::set<int> positionsOfPattern(const std::string& sFormula, const std::string& sPattern) {
    std::set<int> positions; //set intow positions
    size_t pos = sFormula.find(sPattern, 0); //znajdz sPattern w sFormula od pozycji 0
    while (pos != std::string::npos) { //dopoki sPattern jest w sFormula
        positions.insert(pos); //dodaj pozycje do setu
        pos = sFormula.find(sPattern, pos + 1); //znajdz sPattern w sFormula od pozycji pos + 1
    }
    return positions; //zwroc set
}


std::string subString(const std::string& string1, const std::string& string2) {

    size_t found = string1.rfind(string2); //znajdz string2 w string1 od konca
    if (found != std::string::npos) { //jesli string2 jest w string1
        std::string result = string1; //string result = string1
        result.erase(found, string2.length()); //usun z result string2
        return result; //zwroc result
    }
    return string1; //jesli string2 nie jest w string1 zwroc string1
}

std::string addString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}

std::string mulString(const std::string& string1, const std::string& string2) {
    if (string2.empty()) return string1; //jesli string2 jest pusty zwroc string1

    std::string result = string1; // string result = string1
    std::set<int> positions = positionsOfPattern(string1, string2.substr(0, 1)); // znajdz pozycje pierwszego znaku string2 w string1
    int offset = 0; // zmienna do śledzenia aktualnej pozycji po wstawieniu
    for (int position : positions) { // dla kazdej pozycji
        result.insert(position + offset + 1, string2.substr(1, string2.length() - 1)); // wstaw string2 do result od pozycji + 1
        offset += string2.length() - 1; // zaktualizuj offset
    }
    return result; // zwroc result
}

std::string divString(const std::string& string1, const std::string& string2) {
    if (string2.empty()) {
        return string1; // If string2 is empty, return string1 unchanged
    }

    std::string result = string1; // string result = string1
    std::set<int> positions = positionsOfPattern(string1, string2.substr(0, 1)); // znajdz pozycje pierwszego znaku string2 w string1
    int offset = 0; // zmienna do śledzenia aktualnej pozycji do usunięcia

    for (int position : positions) { // dla kazdej pozycji
        result.erase(position - offset + 1, string2.length() - 1); // usuń substring od pozycji + 1
        offset += string2.length() - 1; // zaktualizuj offset
    }

    return result; // zwroc result
}

