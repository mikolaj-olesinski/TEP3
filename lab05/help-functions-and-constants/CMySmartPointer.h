#include "CRefCounter.h"

template <typename T>
class CMySmartPointer
{
public:
    CMySmartPointer(T *pcPointer)
    {
        pc_pointer = pcPointer;
        pc_counter = new CRefCounter();
        pc_counter->iAdd();
    }

    CMySmartPointer(const CMySmartPointer &pcOther)
    {
        pc_pointer = pcOther.pc_pointer;
        pc_counter = pcOther.pc_counter;
        pc_counter->iAdd();
    }

    ~CMySmartPointer()
    {
        if (pc_counter->iDec() == 0)
        {
            delete pc_pointer;
            delete pc_counter;
        }
    }

    CMySmartPointer &operator=(const CMySmartPointer &pcOther)
    {
        if (this != &pcOther) // Zapobiegamy przypisaniu do samego siebie
        {
            // Dekrementujemy licznik dla bieżącego obiektu
            if (pc_counter->iDec() == 0)
            {
                delete pc_pointer;
                delete pc_counter;
            }

            // Przypisujemy wartość od innego obiektu
            pc_pointer = pcOther.pc_pointer;
            pc_counter = pcOther.pc_counter;
            pc_counter->iAdd();
        }

        return *this;
    }

    T &operator*() { return (*pc_pointer); }
    T *operator->() { return (pc_pointer); }

private:
    CRefCounter *pc_counter;
    T *pc_pointer;
};
