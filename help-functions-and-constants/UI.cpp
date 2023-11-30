#include <iostream>
#include <string>
#include <sstream>
#include "../cTree/cTree.h"


void UI(){
    cTree Tree;
    std::string line; // wczytana linia
    std::string command; // komenda
    std::string rest; // reszta linii po komendzie

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Dostepne komendy:" << std::endl;
    std::cout << "enter <formula> - dodaje drzewo" << std::endl;
    std::cout << "printTree - wypisuje drzewo" << std::endl;
    std::cout << "print - wypisuje formule" << std::endl;
    std::cout << "comp <arg1> <arg2> ... - oblicza wartosc formuly" << std::endl;
    std::cout << "join <formula> - dolacza drzewo" << std::endl;
    std::cout << "vars - wypisuje zmienne" << std::endl;
    std::cout << "help - wypisuje dostepne komendy" << std::endl;
    std::cout << "exit - wychodzi z programu" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;


    while (true) {

        rest = "";
        std::cout << "Podaj komende: ";
        std::getline(std::cin, line); // wczytanie calej linii
        std::istringstream iss(line); // utworzenie strumienia z linii


        if (iss >> command) {
            std::getline(iss >> std::ws, rest);
        } else {
            std::cout << "Blad podczas wczytywania komendy." << std::endl;
            continue;
        }

        if (command == "enter") {
            std::vector<std::string> formula = format(rest);
            if (isPN(formula)){
                Tree.enter(formula);
                std::cout << "Dodano drzewo " << std::endl;
            } else std::cout << "Wpisano zla formule" << std::endl;


        } else if (command == "printTree") {
            Tree.printBT();

        } else if (command == "print") {
            std::vector<std::string> formula = Tree.getPrefix();
            for (const auto& s : formula) {
                std::cout << s << " ";
            }
            std::cout << std::endl;

        }else if (command == "comp") {
            std::vector<std::string> formula = format(rest);
            if (formula.size() != Tree.findVariables().size()) std::cout << "wpisano zla ilosc argumentow" << std::endl;
            else if (!checkIfOnlyNumbers(formula)) std::cout << "wpisz tylko liczby jako argumenty" << std::endl;
            else {
                int result = Tree.compute(formula);
                std::cout << "Wynik: " << result << std::endl;
            }


        } else if (command == "join") {
            std::vector<std::string> formula = format(rest);
            if (isPN(formula)){
                Tree.join(formula);
                std::cout << "dolaczono drzewo " << std::endl;
            } else std::cout << "Wpisano zla formule" << std::endl;


        } else if (command == "vars"){
            std::set<std::string> vars = Tree.findVariables();
            std::cout << "Znalezione zmienne: ";
            for (const auto& s : vars) {
                std::cout << s << " ";
            }
            std::cout << std::endl;

        }else if (command == "help") {
            std::cout << "----------------------------------------------------" << std::endl;
            std::cout << "Dostepne komendy:" << std::endl;
            std::cout << "enter <formula> - dodaje drzewo" << std::endl;
            std::cout << "printTree - wypisuje drzewo" << std::endl;
            std::cout << "print - wypisuje formule" << std::endl;
            std::cout << "comp <arg1> <arg2> ... - oblicza wartosc formuly" << std::endl;
            std::cout << "join <formula> - dolacza drzewo" << std::endl;
            std::cout << "vars - wypisuje zmienne" << std::endl;
            std::cout << "help - wypisuje dostepne komendy" << std::endl;
            std::cout << "exit - wychodzi z programu" << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;

        }else if (command == "exit") {
            std::cout << "Wyjscie z programu." << std::endl;
            break;
        } else {
            std::cout << "Nieznana komenda." << std::endl;
        }

        std::cout << std::endl;
    }

}

