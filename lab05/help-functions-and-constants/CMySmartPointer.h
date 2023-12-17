#include "CRefCounter.h"

template <typename T>
class CMySmartPointer
{
public:
    CMySmartPointer(T *pcPointer) // konstruktor
    {
        pc_pointer = pcPointer;  // przypisujemy wskaźnik
        pc_counter = new CRefCounter(); // tworzymy licznik referencji
        pc_counter->iAdd(); // zwiększamy licznik referencji
    }

    CMySmartPointer(const CMySmartPointer &pcOther) // konstruktor kopiujący
    {
        pc_pointer = pcOther.pc_pointer; // przypisujemy wskaźnik
        pc_counter = pcOther.pc_counter; // przypisujemy licznik referencji
        pc_counter->iAdd(); // zwiększamy licznik referencji
    }

    ~CMySmartPointer() // destruktor
    {
        if (pc_counter->iDec() == 0) // jeśli licznik referencji osiągnął wartość 0, to usuwamy obiekt
        {
            delete pc_pointer; // usuwamy obiekt
            delete pc_counter; // usuwamy licznik referencji
        }
    }

    CMySmartPointer &operator=(const CMySmartPointer &pcOther) // operator przypisania
    {
        if (this != &pcOther) // sprawdzamy, czy nie przypisujemy do samego siebie
        {
            if (pc_counter->iDec() == 0) // jeśli licznik referencji osiągnął wartość 0, to usuwamy obiekt
            {
                delete pc_pointer; // usuwamy obiekt
                delete pc_counter; // usuwamy licznik referencji
            }

            pc_pointer = pcOther.pc_pointer; // przypisujemy wskaźnik
            pc_counter = pcOther.pc_counter; // przypisujemy licznik referencji
            pc_counter->iAdd(); // zwiększamy licznik referencji
        }

        return *this; // zwracamy obiekt CMySmartPointer
    }

    T &operator*() { return (*pc_pointer); } // operator gwiazdki (dereferencji)
    T *operator->() { return (pc_pointer); } // operator strzałki

private:
    CRefCounter *pc_counter; // licznik referencji
    T *pc_pointer;          // wskaznik na obiekt
};
