#include "Bstablo.h"
/*#ifndef ASP2DZ2_BSTABLO_H
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

*/
struct linija{
    long long int racun,korisnik,taksa;
    double stanje;
    linija() = default;
    linija( long long int racun,long long int korisnik,long long int taksa,double stanje):racun(racun),korisnik(korisnik),taksa(taksa),stanje(stanje){};
};
struct korisnik{
    long long int id = 0;
    string ime,prezime,email;
    korisnik() = default;
    korisnik(long long int id, string &ime, string &prezime, string &email): id(id),ime(ime),prezime(prezime),email(email){};
};
linija split(string str, char del){
    string temp = "";
    int k = 1;
    long long int racun,korisnik,taksa;
    double stanje = 0;
    for(int i=0; i<(int)str.size(); i++){
        if(str[i] != del){
            temp += str[i];
        }
        else{
            if (k == 1) racun = stoll(temp);
            else if (k == 3) korisnik = stoll(temp);
            else if(k == 5) taksa = stoll(temp);
            temp = "";
            k++;
        }
    }
    if(k == 6) stanje = stod(temp);
    linija l = linija(racun,korisnik,taksa,stanje);
    return l;
}
korisnik splitk(string str, char del){
    string temp = "";
    int k = 1;
    long long int id;
    string ime, prezime ,email;
    for(int i=0; i<(int)str.size(); i++){
        if(str[i] != del){
            temp += str[i];
        }
        else{
            if (k == 1) id = stoll(temp);
            else if ( k == 2) ime = temp;
            else if (k == 3) prezime = temp;
            else if(k == 4) email = temp;
            temp = "";
            k++;
        }
    }
    korisnik kk = korisnik(id, ime, prezime, email);
    return kk;
}
Bstablo Bstablo::dodajElement(long long int s) {
    Cvor::tabela t = Cvor::tabela(s);
    Cvor *trenutni = koren;
    while(1) {
            if (trenutni->list()) break;
            for (int i = 0; i < trenutni->kljucevi.size(); i++) {
                if (i == 0 && (t.ca_id) < (trenutni->kljucevi[i].ca_id)) {
                    trenutni = trenutni->kljucevi[i].levi;
                    break;
                } else if (i == (trenutni->kljucevi.size() - 1) && (t.ca_id) > (trenutni->kljucevi[i].ca_id)) {
                    trenutni = trenutni->kljucevi[i].desni;
                    break;
                } else if (i!= 0 && (t.ca_id) > (trenutni->kljucevi[i - 1].ca_id) &&(t.ca_id) < (trenutni->kljucevi[i].ca_id)) {
                    trenutni = trenutni->kljucevi[i].levi;
                    break;
                }
            }
        }
        if (trenutni->kljucevi.size() < m - 1){
            trenutni->dodajkljuc(t);
        }
        else {
            trenutni = trenutni->dodajkljuc(t);
            while(trenutni->kljucevi.size() == m){
                trenutni = cepanje(trenutni);
            }
        }
    return *this;
}
Cvor *Bstablo::cepanje(Cvor *trenutni) {
    int i = (trenutni->kljucevi.size())/2;
    if(trenutni->kljucevi.size()%2 == 0) i--;
    Cvor :: tabela srednji = trenutni->kljucevi[i];
    Cvor *desni = new Cvor();
    int m = trenutni->kljucevi.size();
    for(int k = i+1; k<m;k++){
        desni->kljucevi.insert(desni->kljucevi.begin()+ k-i-1,trenutni->kljucevi[k]);
    }
    for(int k = i; k<m ; k++){
        trenutni->kljucevi.erase(trenutni->kljucevi.begin()+k);
    }
    Cvor *levi = trenutni;
    srednji.levi = levi;
    if(!desni->list()) {
        for (int d = 0; d < desni->kljucevi.size(); d++) {
            desni->kljucevi[d].levi->otac = desni;
            desni->kljucevi[d].desni->otac = desni;
        }
    }
    srednji.desni = desni;
    if(trenutni == koren){
        koren = new Cvor();
        levi->otac = koren;
        desni->otac = koren;
        koren->kljucevi.push_back(srednji);
        return koren;
    } else {
        trenutni = trenutni->otac;
        levi->otac = trenutni;
        desni->otac = trenutni;
        trenutni->dodajkljuc(srednji);
        return trenutni;
    }
}
void Bstablo::ispisStabla() {
    queue<Cvor *> red;
    Cvor *liner = new Cvor(), *trenutan;
    liner->kljucevi.emplace_back(-1);
    red.push(koren);
    red.push(liner);
    while (!red.empty()) {
        trenutan = red.front();
        red.pop();
        if (trenutan->kljucevi[0].ca_id == -1) {
            if (!red.empty()) {
                red.push(trenutan);
                cout << endl;
            }
        } else {
            for (Cvor::tabela i: trenutan->kljucevi) {
                cout << i.ca_id <<"(";
                for(Cvor::tabela::elem *curr = i.prvi; curr; curr = curr->sledeci){
                    cout<<curr->racun;
                    if(curr != i.poslednji) cout<<',';
                }
                cout<<")|";
                if (i.ca_id == trenutan->kljucevi[0].ca_id && i.levi != nullptr) red.push(i.levi);
                if (i.desni != nullptr) red.push(i.desni);
            }
            cout << "       ";
        }
    }
}
Bstablo Bstablo::stvoriStablo(long long int s, long long int racun , long long int taksa, double stanje) {
    Cvor::tabela t = Cvor::tabela(s);
    koren = new Cvor();
    koren->kljucevi.push_back(t);
    koren->dodajRacun(0,racun,taksa,stanje);
    return *this;
}
Cvor *Bstablo::pretraga(long long int s, int *num) {
    Cvor *trenutni = koren;
    int k = 0, i, high, low;
    while(trenutni){
        high = trenutni->kljucevi.size();
        low = 0;
        while(high>=low){
            i = (high + low)/2;
            ++(*num);
            if (trenutni->kljucevi[i].ca_id == s) {
                return trenutni;
            } else if (i == 0 && s < (trenutni->kljucevi[i].ca_id)) {
                trenutni = trenutni->kljucevi[i].levi;
                break;
            } else if (i == (trenutni->kljucevi.size() - 1) && s> (trenutni->kljucevi[i].ca_id)) {
                trenutni = trenutni->kljucevi[i].desni;
                break;
            } else if (i!= 0 && s > (trenutni->kljucevi[i - 1].ca_id) && s < (trenutni->kljucevi[i].ca_id)) {
                trenutni = trenutni->kljucevi[i].levi;
                break;
            }else if(i!=(trenutni->kljucevi.size()-1) && s>trenutni->kljucevi[i].ca_id && s<trenutni->kljucevi[i+1].ca_id){
                trenutni = trenutni->kljucevi[i].desni;
                break;
            }
            else if( s>trenutni->kljucevi[i].ca_id) low = i+1;
            else if(s<trenutni->kljucevi[i].ca_id) high = i-1;
        }
    }
    num = &k;
    return nullptr;
}
Bstablo Bstablo::stvoriIndeks(string file) {
    int *koraci;
    ifstream dat;
    dat.open(file);
    if(!dat.is_open()) exit(1);
    int num = 0;
    linija k;
    string line;
    while(getline(dat,line)){
        k = split(line,'|');
        if(!num){
            this->stvoriStablo(k.korisnik,k.racun,k.taksa,k.stanje);
            num = 1;
        }else{
            Cvor *trenutni = pretraga(k.korisnik,koraci);
            if(trenutni == nullptr){
                this->dodajElement(k.korisnik);
            }
            trenutni = pretraga((k.korisnik), koraci);
            for(int i = 0; i<trenutni->kljucevi.size();i++){
                if(trenutni->kljucevi[i].ca_id == k.korisnik){
                    trenutni->dodajRacun(i,k.racun,k.taksa,k.stanje);
                }
            }
        }
    }
    dat.close();
    return *this;
}
void Bstablo::izbrisiStablo() {
    queue<Cvor *> red;
    Cvor *trenutan;
    red.push(koren);
    while (!red.empty()) {
        trenutan = red.front();
        red.pop();
        for (Cvor::tabela i: trenutan->kljucevi) {
            if (i.ca_id == trenutan->kljucevi[0].ca_id && i.levi != nullptr) red.push(i.levi);
            if (i.desni != nullptr) red.push(i.desni);
        }
        trenutan->obrisiCvor();
    }
    koren = nullptr;
}
void Bstablo::ispisRacunaKorisnika() {
    int a = 0;
    int *koraci = &a;
    cout<<"Unesite ID korisnika : ";
    long long int id;
    cin>>id;
    Cvor *trenutni = pretraga(id,koraci);
    cout<<"Broj potrenih koraka za pretragu je :" <<*koraci<<endl;
    ofstream output("Racuni.txt");
    ifstream dat;
    dat.open("Customer.txt");
    string line;
    if(!dat.is_open()) exit(1);
    while(getline(dat,line)){
        korisnik k = splitk(line, '|');
        if(k.id == id) {
            if(trenutni == nullptr){
                output<<k.id<<"|"<<k.ime<<"|"<<k.prezime<<"|"<<k.email<<"|null|null|null|null";
            } else{
                for(int i = 0; i<trenutni->kljucevi.size(); i++){
                    if(trenutni->kljucevi[i].ca_id == id){
                        for(Cvor::tabela::elem *curr = trenutni->kljucevi[i].prvi; curr; curr = curr->sledeci){
                            output<<fixed<<showpoint<<setprecision(2)<<k.id<<"|"<<k.ime<<"|"<<k.prezime<<"|"<<k.email<<"|"<<curr->racun<<"|"<<k.id<<"|"<<curr->taksa<<"|"<<curr->stanje<<endl;
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
    output.close();
    dat.close();
}
Bstablo Bstablo::dodajZapis() {
    int a = 0;
    int *koraci = &a;
    string racun = "";
    cout<<"Unesite podatke od racuna: ";
    while(racun == "") getline(cin, racun);
    linija l = split(racun, '|');
    Cvor *trenutni = pretraga(l.korisnik,koraci);
    if(trenutni == nullptr){
        dodajElement(l.korisnik);
    } else {
        for(int i = 0; i<trenutni->kljucevi.size();i++){
            if(trenutni->kljucevi[i].ca_id == l.korisnik){
                for(Cvor::tabela::elem *curr = trenutni->kljucevi[i].prvi; curr; curr = curr->sledeci){
                    if(curr->racun == l.racun){
                        cout<<"Ovaj zapis vec postoji u indeksu"<<endl;
                        return *this;
                    }
                }
            }
        }
    }
    trenutni = pretraga(l.korisnik,koraci);
    for(int i = 0; i<trenutni->kljucevi.size();i++){
        if(trenutni->kljucevi[i].ca_id == l.korisnik){
            trenutni->dodajRacun(i,l.racun,l.taksa,l.stanje);
        }
    }
    return *this;
}
Bstablo &Bstablo::izbrisiElement(long long int s, bool is) {
    int r = 0, a = 0;
    int *koraci = &a;
    Cvor *trenutni = pretraga(s,koraci);
    Cvor *sledbenik = nadjiSledbenika(s);
    if(!trenutni->list()){
        for(int i = 0; i<trenutni->kljucevi.size();i++){
            if(trenutni->kljucevi[i].ca_id == s){
                long long int tmp = sledbenik->kljucevi[0].ca_id;
                sledbenik->kljucevi[0].ca_id = trenutni->kljucevi[i].ca_id;
                trenutni->kljucevi[i].ca_id = tmp;
                Cvor::tabela::elem *prvi = sledbenik->kljucevi[0].prvi;
                Cvor::tabela::elem *poslednji = sledbenik->kljucevi[0].poslednji;
                sledbenik->kljucevi[0].prvi = trenutni->kljucevi[i].prvi;
                sledbenik->kljucevi[0].poslednji = trenutni->kljucevi[i].poslednji;
                trenutni->kljucevi[i].prvi = prvi;
                trenutni->kljucevi[i].poslednji = poslednji;
                trenutni = sledbenik;
                break;
            }
        }
    }
    Cvor *temp = nullptr;
    if(trenutni == nullptr){
        cout<<"Nije izbrisan nijedan zapis!"<<endl;
    }else{
        if(is) {
            for (Cvor::tabela t: trenutni->kljucevi) {
                if (t.ca_id == s) {
                    cout << "Obrisani zapisi su: " << endl;
                    for (Cvor::tabela::elem *curr = t.prvi; curr; curr = curr->sledeci) {
                        cout << fixed << showpoint << setprecision(2) << curr->racun << "," << s << "," << curr->taksa
                             << "," << curr->stanje << endl;
                    }
                }
            }
        }
        if(trenutni->kljucevi.size()>min){
            trenutni->obrisiKljuc(s);
        } else{
            trenutni->obrisiKljuc(s);
            while (trenutni->kljucevi.size() < min){
                (*koraci)++;
                Cvor *desni = trenutni->desniBrat();
                Cvor *levi = trenutni->leviBrat();
                Cvor *otac = trenutni->otac;
                if ((desni != nullptr) && (desni->kljucevi.size() > min)) {
                    Cvor::tabela t = desni->kljucevi.front();
                    desni->kljucevi.erase(desni->kljucevi.begin());
                    for (int i = 0; i < otac->kljucevi.size(); i++) {
                        if (otac->kljucevi[i].levi == trenutni) {
                            otac->kljucevi[i].desni = t.levi;
                            if(trenutni->kljucevi.size()) otac->kljucevi[i].levi = trenutni->kljucevi.back().desni;
                            else otac->kljucevi[i].levi = temp;
                            if(t.levi) t.levi->otac = trenutni;
                            t.levi = trenutni;
                            t.desni = desni;
                            trenutni->kljucevi.push_back(otac->kljucevi[i]);
                            otac->kljucevi[i] = t;
                        }
                    }
                }
                else if ((levi != nullptr) && (levi->kljucevi.size() > min)) {
                    Cvor::tabela t = levi->kljucevi.back();
                    levi->kljucevi.erase(levi->kljucevi.begin() + levi->kljucevi.size() - 1);
                    for (int i = 0; i < otac->kljucevi.size(); i++) {
                        if (otac->kljucevi[i].desni == trenutni) {
                            otac->kljucevi[i].levi = t.desni;
                            if(trenutni->kljucevi.size()) otac->kljucevi[i].desni = trenutni->kljucevi[0].levi;
                            else otac->kljucevi[i].desni = temp;
                            if(t.desni) t.desni->otac = trenutni;
                            t.levi = levi;
                            t.desni  = trenutni;
                            trenutni->kljucevi.insert(trenutni->kljucevi.begin(), otac->kljucevi[i]);
                            otac->kljucevi[i] = t;
                        }
                    }
                }
                else {
                    if (desni != nullptr) {
                        for (int i = 0; i < otac->kljucevi.size(); i++) {
                            if (otac->kljucevi[i].levi == trenutni) {
                                if (trenutni->kljucevi.size()) otac->kljucevi[i].levi = otac->kljucevi[i].levi->kljucevi.back().desni;
                                else otac->kljucevi[i].levi = temp;
                                otac->kljucevi[i].desni = otac->kljucevi[i].desni->kljucevi.front().levi;
                                trenutni->kljucevi.push_back(otac->kljucevi[i]);
                                for (Cvor::tabela k: desni->kljucevi) trenutni->kljucevi.push_back(k);
                                if (i) otac->kljucevi[i - 1].desni = trenutni;
                                if (i != otac->kljucevi.size() - 1) otac->kljucevi[i + 1].levi = trenutni;
                                for(Cvor::tabela t:desni->kljucevi) {
                                    if(t.levi) t.levi->otac = trenutni;
                                    if(t.desni) t.desni->otac = trenutni;
                                }
                                otac->kljucevi.erase(otac->kljucevi.begin() + i);
                                if(temp)temp->otac = trenutni;
                                for(int i = 1; i<trenutni->kljucevi.size();i++){
                                    trenutni->kljucevi[i].levi = trenutni->kljucevi[i-1].desni ;//proveri
                                }
                                temp = trenutni;
                            }
                        }
                    } else if (levi != nullptr) {
                        for (int i = 0; i < otac->kljucevi.size(); i++) {
                            if (otac->kljucevi[i].desni == trenutni) {
                                if (trenutni->kljucevi.size()) otac->kljucevi[i].desni = otac->kljucevi[i].desni->kljucevi.front().levi;
                                else otac->kljucevi[i].desni = temp;
                                otac->kljucevi[i].levi = otac->kljucevi[i].levi->kljucevi.back().desni;
                                levi->kljucevi.push_back(otac->kljucevi[i]);
                                for (Cvor::tabela k: trenutni->kljucevi) levi->kljucevi.push_back(k);
                                if (i) otac->kljucevi[i - 1].desni = levi;
                                if (i != (otac->kljucevi.size() - 1)) otac->kljucevi[i + 1].levi = levi;
                                otac->kljucevi.erase(otac->kljucevi.begin() + i);
                                for(int i = 1; i<levi->kljucevi.size();i++){
                                    levi->kljucevi[i].levi= levi->kljucevi[i-1].desni  ;//proveri
                                }
                                if(temp)temp->otac = levi;
                                temp = levi;
                            }
                        }
                    }
                    if(otac == koren && koren->kljucevi.size()==0) {
                        koren = temp;
                        for(int i = 0;i<temp->kljucevi.size();i++){
                            if(temp->kljucevi[i].levi) temp->kljucevi[i].levi->otac = koren;
                            if(temp->kljucevi[i].desni) temp->kljucevi[i].desni->otac = koren;
                        }
                        r = 1;
                    }
                }
                trenutni = otac;
                if(trenutni == nullptr) break;
                if(r == 1) break;
                if(trenutni == koren){
                    break;
                }
            }
        }
    }
    cout<<"Broj potrebnih koraka za ovu operaciju je: "<<*koraci<<endl;
    return *this;
}
Cvor *Bstablo::nadjiSledbenika(long long  int s) {
    int a = 0;
    int *koraci = &a;
    Cvor *trenutni = pretraga(s,koraci);
    for(int i = 0; i<trenutni->kljucevi.size();i++){
        if(trenutni->kljucevi[i].ca_id == s){
            trenutni = trenutni->kljucevi[i].desni;
            break;
        }
    }
    while(trenutni){
        if(trenutni->kljucevi.front().levi) trenutni = trenutni->kljucevi.front().levi;
        else break;
    }
    return trenutni;
}
Bstablo Bstablo::izbrisiZapis() {
    int a = 0;
    int *koraci = &a;
    string racun = "";
    cout<<"Unesite podatke od racuna: ";
    while(racun == "") getline(cin, racun);
    linija l = split(racun, '|');
    Cvor *trenutni = pretraga(l.korisnik,koraci);
    if(trenutni == nullptr){
        cout<<"Zapis ne postoji u indeksu."<<endl;
        return *this;
    }else {
        for(int i = 0; i<trenutni->kljucevi.size();i++){
            (*koraci)++;
            if(trenutni->kljucevi[i].ca_id == l.korisnik){
                Cvor::tabela::elem *prev = nullptr;
                cout<<"Broj potrebnih koraka za pretragu je: "<<*koraci<<endl;
                if(trenutni->kljucevi[i].prvi == trenutni->kljucevi[i].poslednji){
                    izbrisiElement(l.korisnik, false);
                    return *this;
                }
                for(Cvor::tabela::elem *curr = trenutni->kljucevi[i].prvi; curr; curr = curr->sledeci){
                    if(curr->racun == l.racun){
                        if(prev){
                            prev->sledeci = curr->sledeci;
                            if(trenutni->kljucevi[i].poslednji == curr) trenutni->kljucevi[i].poslednji = prev;
                        } else{
                            trenutni->kljucevi[i].prvi = curr->sledeci;
                        }
                        delete(curr);
                        return *this;
                    }
                    prev = curr;
                }
            }
        }
    }
    cout<<"Broj potrebnih koraka za pretragu je: "<<*koraci<<endl;
    cout<<"Zapis ne postoji u indeksu."<<endl;
    return *this;
}
Bstablo Bstablo::promeniM(int mi) {
    m = mi;
    max = m-1;
    min = min = ceil((m/2.0))-1;
    return *this;
}


