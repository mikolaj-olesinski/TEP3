#ifndef TEP3_CTREE_H
#define TEP3_CTREE_H

#include <string>
#include "../cNode/cNode.h"
#include <set>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>


template <typename T>
class cTree {
public:

    cTree(const cTree &other); //konstruktor kopiujacy
    cTree(); //konstruktor domyslny
    ~cTree(); //destruktor

    cTree& enter(const std::vector<std::string>& formula); //funkcja tworzaca drzewo z wektora stringow
    cTree& join(cTree &other); //funkcja laczaca 2 drzewa przyjmujaca jako argument drugie drzewo

    T compute(const std::vector<std::string>& valuesOfVariables) const; //funkcja obliczajaca wartosc drzewa

    cTree& operator=(const cTree& other); //operator przypisania
    cTree operator+(const cTree& other) const; //operator dodawania

    std::set<std::string> findVariables() const; //funkcja znajdujaca zmienne w drzewie

    void printBT() const; //funkcja wypisujaca drzewo w formie graficznej

    std::vector<std::string> getPrefix() const; //funkcja zwracajaca drzewo w formie prefixowej



private:

    cNode *cRoot; //korzen drzewa

    T computeNode(cNode* node, const std::vector<std::string>& valuesOfVariables) const; //funkcja obliczajaca rekurencyjnie wartosc drzewa od danego wezla

    cNode* findRightLeafParent() const; //funkcja znajdujaca prawy lisc
    static void findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables); //funkcja znajdujaca zmienne w drzewie za pomoca rekurencji i przekazujaca je do zbioru
    static void replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables); //funkcja zamieniajaca zmienne w drzewie za pomoca rekurencji

    static int maxDepth(cNode* root); //funkcja znajdujaca wysokosc drzewa
    static void getLeavesAtDepth(cNode* node, int currentDepth, int targetDepth, std::vector<cNode*>& leavesByParent); //funkcja znajdujaca liscie na danym poziomie


    static void printBTRecursiveHelp(const std::string& prefix, cNode* node, bool isLeft); //funkcja wypisujaca drzewo za pomoca rekurencji
    static std::vector<std::string> getPrefixRecursiveHelp(cNode *node); //funkcja zwracajaca drzewo w formie prefixowej za pomoca rekurencji
};


#endif
