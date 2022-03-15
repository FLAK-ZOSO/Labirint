#include <iostream>
#include <fstream>
using namespace std;


void stampaScrittaMenu() {
    ifstream fin;
    fin.open("menu.txt", ios::in);
    string testo;
    
    if (fin) {
        while (getline(fin, testo))
            cout << testo << endl;
    } else
        cout << "errore apertura file prova.txt" << endl;
    
    fin.close();
}


int leggiDati(string username) {
    // Leggi il file di testo che chiamiamo utenti.txt
    

    // Controlli se nel file è già registrato il nome utente dell'utente (username)

    // Se è già registrato fai return del suo record

    // Se non è ancora registrato fai return 0
}


void scriviDati(string username) {

}