

#ifndef TEP3_STALE_H
#define TEP3_STALE_H

#include <string>

static const int MAX_AMOUNT_OF_CHILDREN_FOR_ARTH = 2;
static const int MAX_AMOUNT_OF_CHILDREN_FOR_TRIG = 1;
static const std::string OPERATORS[] = {"+", "-", "*", "sin", "cos"};
static const std::string ARTH_OPERATORS[] = {"+", "-", "*"};
static const std::string TRIG_OPERATORS[] = {"sin", "cos"};
static const int OPERATORS_SIZE = sizeof(OPERATORS)/sizeof(OPERATORS[0]);
static const int ARTH_OPERATORS_SIZE = sizeof(ARTH_OPERATORS)/sizeof(ARTH_OPERATORS[0]);
static const int TRIG_OPERATORS_SIZE = sizeof(TRIG_OPERATORS)/sizeof(TRIG_OPERATORS[0]);
#endif


