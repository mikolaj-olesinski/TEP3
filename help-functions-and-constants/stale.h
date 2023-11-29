

#ifndef TEP3_STALE_H
#define TEP3_STALE_H

#include <string>

static const int MAX_AMOUNT_OF_CHILDREN_FOR_ARTH = 2; //maksymalna ilosc dzieci dla operatorow arytmetycznych
static const int MAX_AMOUNT_OF_CHILDREN_FOR_TRIG = 1; //maksymalna ilosc dzieci dla operatorow trygonometrycznych
static const std::string OPERATORS[] = {"+", "-", "*", "sin", "cos"}; //operatorzy
static const std::string ARTH_OPERATORS[] = {"+", "-", "*"}; //operatorzy arytmetyczni
static const std::string TRIG_OPERATORS[] = {"sin", "cos"}; //operatorzy trygonometryczni
#endif


