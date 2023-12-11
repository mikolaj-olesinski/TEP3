#ifndef TEP3_CNODE_H
#define TEP3_CNODE_H
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "../help-functions-and-constants/functions.h"



class cNode {

private:

    cNode(); //konstruktor prywany
    cNode(std::string value); //konstruktor z parametrem
    cNode(const cNode &other); //konstruktor kopiujacy
    ~cNode(); //destruktor


    std::vector<cNode*>* vChildren; //wektor dzieci
    cNode* cParent; //wskaznik na rodzica
    std::string sValue; //wartosc wezla w Stringu

    void cAddtoNode(cNode &newChild); //dodaje wezel do wektora dzieci


    template <typename U>
    friend class cTree; //deklaracja przyjazni z klasa cTree //TODO nie jestem pewien wciaz

};


#endif