class CRefCounter
{
public:
    CRefCounter() { i_count; } // konstruktor
    int iAdd() { return(++i_count); } // inkrementacja
    int iDec() { return(--i_count); }; // dekrementacja
    int iGet() { return(i_count); } // odczyt
private:
    int i_count; // licznik referencji
};