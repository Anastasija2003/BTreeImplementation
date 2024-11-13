#include "cvor.h"
/*#ifndef ASP2DZ2_CVOR_H
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
*/
bool Cvor::list() {
    for(tabela i: kljucevi){
        if(i.levi != nullptr) return false;
        if(i.desni != nullptr) return false;
    }
    return true;
}
Cvor *Cvor::dodajkljuc(tabela &t) {
    for(int i = 0; i<kljucevi.size();  i++){
        if((i == 0 )&& (t.ca_id<(kljucevi[0].ca_id))){
            kljucevi.insert(kljucevi.begin(),t);
            kljucevi[1].levi = kljucevi[0].desni;
            break;
        } else if(i == (kljucevi.size()-1) &&t.ca_id>kljucevi[i].ca_id){
            kljucevi[i].desni = t.levi;
            kljucevi.push_back(t);
            break;
        }
        else if(t.ca_id>kljucevi[i].ca_id && t.ca_id<kljucevi[i+1].ca_id){
            kljucevi.insert(kljucevi.begin()+i+1,t);
            kljucevi[i].desni = kljucevi[i+1].levi;
            kljucevi[i+2].levi = kljucevi[i+1].desni;
            break;
        }
    }
    return this;
}
Cvor *Cvor::dodajRacun(int i ,long long int racun, long long int taksa, double stanje) {
    kljucevi[i].poslednji = (kljucevi[i].prvi?kljucevi[i].poslednji->sledeci:kljucevi[i].prvi) = new tabela::elem(racun,taksa,stanje);
    return this;
}
void Cvor::obrisiCvor() {
    for(tabela t: kljucevi){
        for(tabela::elem *curr = t.prvi;curr;){
            tabela::elem *tmp = curr->sledeci;
            delete(curr);
            curr = tmp;
        }
        t.prvi = nullptr;
        t.poslednji = nullptr;
        t.levi = nullptr;
        t.desni = nullptr;
    }
}
Cvor &Cvor::obrisiKljuc(long long int  s) {
    for(int i = 0;i<kljucevi.size();i++){
        if(kljucevi[i].ca_id == s){
            kljucevi.erase(kljucevi.begin()+i);
            break;
        }
    }
    return *this;
}
Cvor *Cvor::desniBrat() {
    for(int i = 0; i<otac->kljucevi.size();i++){
        if(otac->kljucevi[i].levi == this) {
            return otac->kljucevi[i].desni;
        }
    }
    return nullptr;
}
Cvor *Cvor::leviBrat() {
    for(int i = 0; i<otac->kljucevi.size();i++){
        if( otac->kljucevi[i].desni ==this){
            return otac->kljucevi[i].levi;
        }
    }
    return nullptr;
}


