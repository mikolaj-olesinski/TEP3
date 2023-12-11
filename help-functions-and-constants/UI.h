#include <iostream>
#include <string>
#include <sstream>
#include "../cTree/cTree.h"
#include "../cTree/cTreeHelp.tpp"
#include "../cTree/cTree.tpp"

template <typename>
class UI {
public:
    void run();
private:
    void printHelp();
    bool checkFormulaWithVariables(std::vector<std::string> formula);
    bool checkFormula(std::vector<std::string> formula);

};



const std::string HELP = "help";
const std::string ENTER = "enter";
const std::string VARS = "vars";
const std::string PRINT = "print";
const std::string PRINT_TREE = "printTree";
const std::string COMP = "comp";
const std::string JOIN = "join";
const std::string RESET = "reset";
const std::string EXIT = "exit";


const std::string START_COMMAND = "Podaj komende: ";
const std::string ERROR_COMMAND = "Blad podczas wczytywania komendy.";
const std::string ENTERED_TREE = "Dodano drzewo ";
const std::string WRONG_FORMULA = "Wpisano zla formule";
const std::string WRONG_NUMBER_OF_ARGUMENTS = "wpisano zla ilosc argumentow";
const std::string WRONG_TYPE_OF_ARGUMENTS = "zly format argumentow";
const std::string JOINED_TREE = "dolaczono drzewo ";
const std::string FOUND_VARIABLES = "Znalezione zmienne: ";
const std::string EXIT_PROGRAM = "Wyjscie z programu.";
const std::string UNKNOWN_COMMAND = "Nieznana komenda.";
const std::string RESET_TYPE = "Zresetowano typ drzewa.";
const std::string WRONG_TYPE_OF_TREE = "Nieznany typ drzewa.";
const std::string RESULT = "Wynik: ";



void startUIAndDetermineTypeOfTree() {
    int typeOfTree;

    while (true) {
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Dostepne typy drzew:" << std::endl;
        std::cout << "1. int" << std::endl;
        std::cout << "2. double" << std::endl;
        std::cout << "3. string" << std::endl;
        std::cout << "4. exit" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Podaj typ drzewa: ";

        std::cin >> typeOfTree;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (typeOfTree == 1) {
            UI<int> uiInt;
            uiInt.run();
        } else if (typeOfTree == 2) {
            UI<double> uiDouble;
            uiDouble.run();
        } else if (typeOfTree == 3) {
            UI<std::string> uiString;
            uiString.run();
        } else if (typeOfTree == 4) {
            break;
        } else {
            std::cout << WRONG_TYPE_OF_TREE << std::endl;
        }
    }
}

template<typename T>
void UI<T>::run() {

    cTree<T> Tree;
    std::string line; // wczytana linia
    std::string command; // komenda
    std::string rest; // reszta linii po komendzie

    printHelp();

    while (true) {

        rest = "";
        std::cout << START_COMMAND;
        std::getline(std::cin, line); // wczytanie linii
        std::istringstream iss(line); // utworzenie strumienia z linii


        if (iss >> command) {
            std::getline(iss >> std::ws, rest);
        } else {
            std::cout << ERROR_COMMAND << std::endl;
            continue;
        }

        if (command == ENTER) {
            std::vector<std::string> formula = format(rest);
            if (checkFormulaWithVariables(formula) && isPN(formula)){ //pamietac by checkFormula bylo pierwsze
                Tree.enter(formula);
                std::cout << ENTERED_TREE << std::endl;
            } else std::cout << WRONG_FORMULA << std::endl;


        } else if (command == PRINT_TREE) {
            Tree.printBT();

        } else if (command == PRINT) {
            std::vector<std::string> formula = Tree.getPrefix();
            for (const auto& s : formula) {
                std::cout << s << " ";
            }
            std::cout << std::endl;

        }else if (command == COMP) {
            std::vector<std::string> formula = format(rest);
            if (formula.size() != Tree.findVariables().size()) std::cout << WRONG_NUMBER_OF_ARGUMENTS << std::endl;
            else if (!checkFormula(formula)) std::cout << WRONG_FORMULA << std::endl;
            else {
                T result = Tree.compute(formula);
                std::cout << RESULT << result << std::endl;
            }


        } else if (command == JOIN) {
            std::vector<std::string> formula = format(rest);
            if (checkFormulaWithVariables(formula) && isPN(formula)){
                Tree.join(((new cTree<T>)->enter(formula)));
                std::cout << JOINED_TREE << std::endl;
            } else std::cout << WRONG_FORMULA << std::endl;


        } else if (command == VARS){
            std::set<std::string> vars = Tree.findVariables();
            std::cout << FOUND_VARIABLES;
            for (const auto& s : vars) {
                std::cout << s << " ";
            }
            std::cout << std::endl;

        }else if (command == HELP) {
            printHelp();
        }else if (command == EXIT) {
            delete &Tree;
            std::cout << EXIT_PROGRAM << std::endl;
            break;
        }else if (command == RESET) {
            std::cout << RESET_TYPE << std::endl;
            startUIAndDetermineTypeOfTree();
        } else {
            std::cout << UNKNOWN_COMMAND << std::endl;
        }

        std::cout << std::endl;
    }

}

template<typename T>
void UI<T>::printHelp() {
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "help - wypisuje dostepne komendy" << std::endl;
    std::cout << "enter - dodaje drzewo" << std::endl;
    std::cout << "printTree - wypisuje drzewo" << std::endl;
    std::cout << "print - wypisuje formule" << std::endl;
    std::cout << "comp - oblicza wartosc formuly" << std::endl;
    std::cout << "join - dolacza drzewo" << std::endl;
    std::cout << "vars - wypisuje zmienne" << std::endl;
    std::cout << "reset - resetuje typ drzewa" << std::endl;
    std::cout << "exit - wychodzi z programu" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}


template<>
bool UI<int>::checkFormula(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isInt(s)) return false;
    }
    return true;
}

template<>
bool UI<double>::checkFormula(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isDouble(s)) return false;
    }
    return true;
}

template<>
bool UI<std::string>::checkFormula(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isString(s)) return false;
    }
    return true;
}

template<>
bool UI<int>::checkFormulaWithVariables(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isInt(s) && !isVariable(s) && (!isOperator(s))) return false;
    }
    return true;
}

template<>
bool UI<double>::checkFormulaWithVariables(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isDouble(s) && !isVariable(s) && !isOperator(s)) return false;
    }
    return true;
}

template<>
bool UI<std::string>::checkFormulaWithVariables(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isString(s) && !isOperator(s) && !isStringVariable(s)) return false;
    }
    return true;
}

#ifndef TEP3_UI_H
#define TEP3_UI_H

#endif //TEP3_UI_H

//TODO blad o wpisaniu zlego typu