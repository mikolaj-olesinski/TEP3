#ifndef CNODE_H
#define CNODE_H

class cNode
{
public:

    cNode() = default;
    ~cNode() = default;

    virtual double compute() const = 0;
    virtual std::string getValue() const { return ""; }

    friend class cTree;

};


#endif //CNODE_H
