#ifndef CNODE_H
#define CNODE_H

class cNode
{
public:
    cNode* parent; //TODO czy potrzebny parent jeszcze nwm

    cNode(): parent(nullptr) {};
    ~cNode(){};

    virtual double compute() const = 0;
    void cAddtoNode(cNode &newChild) {};

    friend class cTree;

};


#endif //CNODE_H
