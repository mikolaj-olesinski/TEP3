#ifndef TEP3_CNODE_H
#define TEP3_CNODE_H
#include <vector>
#include <string>
#include <algorithm>
#include "../help-functions-and-constants/functions.h"


class cNode {

private:

    cNode(); //konstruktor prywany
    cNode(std::string sValue); //konstruktor z parametrem
    cNode(const cNode &other); //konstruktor kopiujacy
    ~cNode(); //destruktor


    std::vector<cNode*>* vChildren; //wektor dzieci
    cNode* cParent; //wskaznik na rodzica
    std::string sValue; //wartosc wezla

    void cAddtoNode(cNode &newChild); //dodaje wezel do wektora dzieci

    friend class cTree;

};


#endif