#pragma once

#include <string>

static const int MAX_AMOUNT_OF_CHILDREN_FOR_ARTH = 2; //maksymalna ilosc dzieci dla operatorow arytmetycznych
static const int MAX_AMOUNT_OF_CHILDREN_FOR_TRIG = 1; //maksymalna ilosc dzieci dla operatorow trygonometrycznych
static const std::string OPERATORS[] = {"+", "-", "*", "/" ,"sin", "cos"}; //operatorzy
static const std::string ARTH_OPERATORS[] = {"+", "-", "*", "/"}; //operatorzy arytmetyczni
static const std::string TRIG_OPERATORS[] = {"sin", "cos"}; //operatorzy trygonometryczni


const std::string START_COMMAND = "Podaj komende: ";
const std::string ERROR_COMMAND = "Blad podczas wczytywania komendy.";
const std::string ENTERED_TREE = "Dodano drzewo ";
const std::string WRONG_FORMULA = "Wpisano zla formule";
const std::string WRONG_NUMBER_OF_ARGUMENTS = "wpisano zla ilosc argumentow";
const std::string JOINED_TREE = "dolaczono drzewo ";
const std::string FOUND_VARIABLES = "Znalezione zmienne: ";
const std::string EXIT_PROGRAM = "Wyjscie z programu.";
const std::string UNKNOWN_COMMAND = "Nieznana komenda.";
const std::string RESET_TYPE = "Zresetowano typ drzewa.";
const std::string WRONG_TYPE_OF_TREE = "Nieznany typ drzewa.";
const std::string RESULT = "Wynik: ";





