#include <iostream>
using namespace std;
#include "Bstablo.h"

void menu(){
    int k = 0;
    Bstablo b(1);
    while (k != 8){
        cout << "MENI:\n"
                "1.Stvoriti indeks\n"
                "2.Ispisati indeks na standardni izlaz\n"
                "3.Ispisati podatke o zadatom korisniku i svim njegovim racunima\n"
                "4.Dodati novi racun u indeks\n"
                "5.Obrisati zadati racun iz indeksa\n"
                "6.Brisanje svih racuna zadatkog korisnika iz indeksa\n"
                "7.Unistiti indeks\n"
                "8.Izaci iz programa\n"
                "Unesite zeljenu opciju:  ";
        cin >> k;
        while(k<1 || k>8) {
            cout << "MENI:\n"
                    "1.Stvoriti indeks\n"
                    "2.Ispisati indeks na standardni izlaz\n"
                    "3.Ispisati podatke o zadatom korisniku i svim njegovim racunima\n"
                    "4.Dodati novi racun u indeks\n"
                    "5.Obrisati zadati racun iz indeksa\n"
                    "6.Brisanje svih racuna zadatkog korisnika iz indeksa\n"
                    "7.Unistiti indeks\n"
                    "8.Izaci iz programa\n"
                    "Unesite zeljenu opciju:  ";
            cin >> k;
        }
        if(k == 1){
            cout<<"Unesite red stabla: ";
            int m;
            cin>>m;
            string fajl;
            cout<<"Unesite ime fajla nad kojim se pravi indeks: ";
            cin>>fajl;
            b.promeniM(m);
            b.stvoriIndeks(fajl);
        } else if(k == 2){
            b.ispisStabla();
            cout<<endl;
        }
        else if ( k == 3) b.ispisRacunaKorisnika();
        else if( k == 4) b.dodajZapis();
        else if ( k == 5) b.izbrisiZapis();
        else if( k == 6) {
            cout<<"Unesite ID korisnika: ";
            long long id;
            cin>>id;
            b.izbrisiElement(id,true);
        }
        else if( k == 7) b.izbrisiStablo();
        else if ( k == 8) break;
    }
}
int main() {
    menu();
    return 0;
}
