#ifndef ASP2DZ2_CVOR_H
#define ASP2DZ2_CVOR_H
#include "iostream"
using namespace std;
#include "vector"
#include <fstream>
class Cvor{
    struct tabela{
        long long int ca_id;//id korisnika
        struct elem{
            long long int racun, taksa;
            double stanje;
            elem *sledeci = nullptr;
            elem ( long long int racun , long long int taksa, double stanje) : racun(racun), taksa(taksa), stanje(stanje){};
            elem(const elem &e){
                racun = e.racun;
                taksa = e.taksa;
                stanje = e.stanje;
            }
        };
        elem *prvi = nullptr, *poslednji = nullptr;
        Cvor *levi = nullptr, *desni = nullptr;
        tabela(long long int k): ca_id(k){};
        tabela(const tabela &k){
            ca_id = k.ca_id;
            levi = k.levi;
            desni = k.desni;
            for(elem *curr = k.prvi; curr; curr = curr->sledeci){
                poslednji = (prvi?poslednji->sledeci:prvi) = new elem(curr->racun,curr->taksa,curr->stanje);
            }
        }
    };
    friend class  Bstablo;
    Cvor *otac = nullptr;
    vector <tabela > kljucevi;
public:
    bool list();
    Cvor *dodajRacun(int i ,long long int racun, long long int taksa,double stanje);
    Cvor *dodajkljuc(tabela &t);
    void obrisiCvor();
    Cvor &obrisiKljuc(long long int s);
    Cvor *leviBrat();
    Cvor *desniBrat();
};
#endif
