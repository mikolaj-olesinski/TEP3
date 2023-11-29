#include <iostream>
#include <string>
#include <sstream>
#include "../cTree/cTree.h"


void UI(){
    cTree Tree;
    std::string line;
    std::vector<std::string> formula;
    std::string command;
    std::string rest;

    while (true) {

        rest = "";
        std::cout << "Podaj komende: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);


        if (iss >> command) {
            std::getline(iss >> std::ws, rest);
        } else {
            std::cout << "Blad podczas wczytywania komendy." << std::endl;
            continue; // Ponowne wczytanie komendy
        }

        if (command == "enter") {
            formula = format(rest);
            if (checkIfPN(formula)){
                Tree = enter(formula);
                std::cout << "Dodano drzewo " << std::endl;
            } else std::cout << "Wpisano zla formule" << std::endl;


        } else if (command == "print") {
            printBT(Tree.cRoot);

        } else if (command == "comp") {
            formula = format(rest);
            if (formula.size() != Tree.findVariables().size()) std::cout << "wpisano zla ilosc argumentow" << std::endl;
            else if (!checkIfOnlyNumbers(formula)) std::cout << "wpisz tylko liczby jako argumenty" << std::endl;
            else {
                int result = Tree.compute(formula);
                std::cout << "Wynik: " << result << std::endl;
            }


        } else if (command == "join") {

            if (checkIfPN(formula)){
                Tree.join(formula);
                std::cout << "dolaczono drzewo " << std::endl;
            } else std::cout << "Wpisano zla formule" << std::endl;


        } else if (command == "vars"){
            std::set<std::string> vars = Tree.findVariables();
            std::cout << "Znalezione zmienne: ";
            for (auto it = vars.begin(); it != vars.end(); ++it) {
                std::cout << *it << " "; //TODO do zmiany
            }
            std::cout << std::endl;
        }
        else if (command == "exit") {
            std::cout << "Wyjscie z programu." << std::endl;
            break;
        } else {
            std::cout << "Nieznana komenda." << std::endl;
        }
    }

}

