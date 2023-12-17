
class cNode
{
public:
    cNode() = default;
    virtual double compute() const = 0;
    virtual ~cNode() = default;

    friend class cTree;

};