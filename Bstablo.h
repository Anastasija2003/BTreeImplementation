#ifndef ASP2DZ2_BSTABLO_H
#define ASP2DZ2_BSTABLO_H
#include "cvor.h"
#include <queue>
#include <math.h>
#include <iomanip>
class Bstablo{
    int m;
    int max = m-1, min = ceil((m/2.0))-1;
    Cvor *koren = nullptr;
public:
    explicit Bstablo(int m): m(m){};
    Bstablo promeniM(int m);
    Cvor *cepanje(Cvor *c);
    Bstablo dodajElement(long long int s);
    Bstablo stvoriStablo(long long int s, long long int racun , long long int taksa, double stanje);
    Bstablo stvoriIndeks(string file);
    Cvor* pretraga(long long int s, int *num);
    void ispisRacunaKorisnika();
    Bstablo &izbrisiElement(long long int s, bool is);
    Cvor *nadjiSledbenika(long long int s);
    void ispisStabla();
    void izbrisiStablo();
    Bstablo dodajZapis();
    Bstablo izbrisiZapis();
};

#endif

