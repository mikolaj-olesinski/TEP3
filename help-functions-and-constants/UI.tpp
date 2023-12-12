#include "UI.h"

void startUIAndDetermineTypeOfTree() {
    int typeOfTree; //zmienna przechowujaca typ drzewa

    while (true) { // petla do momentu podania poprawnego typu drzewa
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Dostepne typy drzew:" << std::endl;
        std::cout << "1. int" << std::endl;
        std::cout << "2. double" << std::endl;
        std::cout << "3. string" << std::endl;
        std::cout << "4. exit" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Podaj typ drzewa: ";

        std::cin >> typeOfTree; // wczytanie typu drzewa
        std::cin.clear();  // czyszczenie flagi bledu
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorowanie blednych znakow

        if (typeOfTree == 1) { // wybor typu drzewa
            UI<int> uiInt; // utworzenie obiektu UI
            uiInt.run(); // uruchomienie UI
        } else if (typeOfTree == 2) {
            UI<double> uiDouble;
            uiDouble.run();
        } else if (typeOfTree == 3) {
            UI<std::string> uiString;
            uiString.run();
        } else if (typeOfTree == 4) { // wyjscie z programu
            break;
        } else {
            std::cout << WRONG_TYPE_OF_TREE << std::endl; // blad przy wyborze typu drzewa
        }
    }
}

template<typename T>
void UI<T>::run() {

    cTree<T> Tree;
    std::string line; // wczytana linia
    std::string command; // komenda
    std::string rest; // reszta linii po komendzie

    printHelp(); // wypisanie dostepnych komend

    while (true) { // petla do momentu podania komendy exit

        rest = ""; // wyczyszczenie lini w ktorym jest formula
        std::cout << START_COMMAND;
        std::getline(std::cin, line); // wczytanie linii
        std::istringstream iss(line); // utworzenie strumienia z linii


        if (iss >> command) { // wczytanie komendy
            std::getline(iss >> std::ws, rest); // wczytanie reszty linii
        } else {
            std::cout << ERROR_COMMAND << std::endl;
            continue;
        }

        if (command == ENTER) {
            std::vector<std::string> formula = format(rest); // formatowanie formuly do wektora stringow
            if (checkFormulaWithVariables(formula) && isPN(formula)){ //pamietac by checkFormula bylo pierwsze
                Tree.enter(formula); // dodanie drzewa
                std::cout << ENTERED_TREE << std::endl;
            } else std::cout << WRONG_FORMULA << std::endl; // blad przy dodawaniu drzewa


        } else if (command == PRINT_TREE) { // wypisanie drzewa w postaci "graficznej"
            Tree.printBT();

        } else if (command == PRINT) {
            std::vector<std::string> formula = Tree.getPrefix(); // pobranie formuly jako prefix
            for (const auto& s : formula) { // wypisanie formuly
                std::cout << s << " ";
            }
            std::cout << std::endl;

        }else if (command == COMP) { // obliczenie wartosci formuly
            std::vector<std::string> formula = format(rest); // formatowanie formuly do wektora stringow
            if (formula.size() != Tree.findVariables().size()) std::cout << WRONG_NUMBER_OF_ARGUMENTS << std::endl; //sprawdzenie czy ilosc argumentow jest poprawna
            else if (!checkFormula(formula)) std::cout << WRONG_FORMULA << std::endl; //sprawdzenie czy typ argumentow jest poprawny
            else {
                T result = Tree.compute(formula); // obliczenie wartosci formuly
                std::cout << RESULT << result << std::endl; // wypisanie wyniku
            }


        } else if (command == JOIN) {
            std::vector<std::string> formula = format(rest); // formatowanie formuly do wektora stringow
            if (checkFormulaWithVariables(formula) && isPN(formula)){ //pamietac by checkFormula bylo pierwsze
                Tree.join(((new cTree<T>)->enter(formula))); // dolaczenie drzewa
                std::cout << JOINED_TREE << std::endl;
            } else std::cout << WRONG_FORMULA << std::endl;


        } else if (command == VARS){
            std::set<std::string> vars = Tree.findVariables(); // znalezienie zmiennych
            std::cout << FOUND_VARIABLES; // wypisanie zmiennych
            for (const auto& s : vars) {
                std::cout << s << " ";
            }
            std::cout << std::endl;

        }else if (command == HELP) {
            printHelp();
        }else if (command == EXIT) {
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
        if (!isInt(s)) return false; // sprawdzenie czy typ argumentow jest poprawny
    }
    return true;
}

template<>
bool UI<double>::checkFormula(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isDouble(s)) return false; // sprawdzenie czy typ argumentow jest poprawny
    }
    return true;
}

template<>
bool UI<std::string>::checkFormula(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isString(s)) return false; // sprawdzenie czy typ argumentow jest poprawny
    }
    return true;
}

template<>
bool UI<int>::checkFormulaWithVariables(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isInt(s) && !isVariable(s) && (!isOperator(s))) return false; // sprawdzenie czy typ argumentow jest poprawny
    }
    return true;
}

template<>
bool UI<double>::checkFormulaWithVariables(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isDouble(s) && !isVariable(s) && !isOperator(s)) return false; // sprawdzenie czy typ argumentow jest poprawny
    }
    return true;
}

template<>
bool UI<std::string>::checkFormulaWithVariables(std::vector<std::string> formula) {
    for (const auto& s : formula) {
        if (!isString(s) && !isArthOperator(s) && !isStringVariable(s)) return false; // sprawdzenie czy typ argumentow jest poprawny
    }
    return true;
}
