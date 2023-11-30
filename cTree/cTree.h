

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


class cTree {
public:
    explicit cTree(cNode &cRoot); //explicit by zapobiec niejawnej konwersji //konstruktor kopiujacy z cNode
    cTree(const cTree &other); //konstruktor kopiujacy
    cTree(); //konstruktor domyslny
    ~cTree(); //destruktor

    cTree& enter(const std::vector<std::string>& formula); //funkcja tworzaca drzewo z wektora stringow
    cTree& join(const cTree &other); //funkcja laczaca 2 drzewa przyjmujaca jako argument drugie drzewo
    cTree& join(const std::vector<std::string>& formula); //funkcja laczaca 2 drzewa przyjmujaca jako argument wektor stringow

    int compute(const std::vector<std::string> formula) const; //funkcja obliczajaca wartosc drzewa

    cTree& operator=(const cTree& other); //operator przypisania
    cTree operator+(const cTree& other) const; //operator dodawania

    std::set<std::string> findVariables() const; //funkcja znajdujaca zmienne w drzewie
    void findVariablesAndReplace(std::vector<std::string> replaceValues); //funkcja znajdujaca zmienne w drzewie i zamieniajaca je na wartosci z wektora

    void printBT() const; //funkcja wypisujaca drzewo w formie graficznej

    std::vector<std::string> getPrefix() const; //funkcja zwracajaca drzewo w formie prefixowej


private:

    cNode *cRoot; //korzen drzewa

    cNode* findRightLeafParent() const; //funkcja znajdujaca prawy lisc
    static void findVariablesRecursive(cNode* currentNode, std::set<std::string>& variables); //funkcja znajdujaca zmienne w drzewie za pomoca rekurencji i przekazujaca je do zbioru
    static void replaceVariableRecursive(cNode* currentNode, std::string& variable, std::vector<std::string>& replaceValues, std::set<std::string>& findVariables); //funkcja zamieniajaca zmienne w drzewie za pomoca rekurencji

    static std::vector<cNode*> getLeavesAtLowestLevel(cNode* node); //funkcja znajdujaca liscie na najnizszym poziomie
    static std::vector<std::vector<cNode*>> segregateLeavesByParent(const std::vector<cNode*>& leaves); //funkcja segregujaca liscie po rodzicach
    static int maxDepth(cNode* root); //funkcja znajdujaca wysokosc drzewa
    static void getLeavesAtDepth(cNode* node, int currentDepth, int targetDepth, std::vector<cNode*>& leavesByParent); //funkcja znajdujaca liscie na danym poziomie


    static void printBTRecursiveHelp(const std::string& prefix, cNode* node, bool isLeft); //funkcja wypisujaca drzewo za pomoca rekurencji
    static std::vector<std::string> getPrefixRecursiveHelp(cNode *node); //funkcja zwracajaca drzewo w formie prefixowej za pomoca rekurencji
};









#endif
