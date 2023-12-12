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

void startUIAndDetermineTypeOfTree();

#ifndef TEP3_UI_H
#define TEP3_UI_H

#endif //TEP3_UI_H
