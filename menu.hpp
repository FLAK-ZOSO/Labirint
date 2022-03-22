#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void stampaScrittaMenu() {
    cout << "LLL             AAAAAA      BBBBBBBBB   IIIII  RRRRRRRRR   IIIII  NNNNNN    NNN TTTTTTTTTTT  " << endl;
    cout << "LLL            AAA  AAA     BBB    BBB   III   RRR    RRR   III   NNN NNN   NNN     TTT      " << endl;
    cout << "LLL           AAA    AAA    BBBBBBBBB    III   RRRRRRRRR    III   NNN  NNN  NNN     TTT      " << endl;
    cout << "LLL          AAAAAAAAAAAA   BBB    BBB   III   RRR RRR      III   NNN   NNN NNN     TTT      " << endl;
    cout << "LLLLLLLLLL  AAA        AAA  BBBBBBBBB   IIIII  RRR  RRRR   IIIII  NNN    NNNNNN     TTT      " << endl;
    cout << "\n                                   By FLAK-ZOSO & AsiaMarcheluzzo" << endl;
}


void stampaDati() {
    // Leggi il file di testo che chiamiamo utenti.txt
    ifstream fin;
    fin.open("utenti.txt", ios::in);
    string testo;

    if (fin) {
        while (getline(fin, testo))
            cout << testo << endl;
    } else {
        // Non esiste il file, quindi lo creiamo
        ofstream fout("utenti.txt", ios::out);
        string classifica[10][2] = {
            {"Bot1", "100000"},
            {"Bot2", "90000"},
            {"Bot3", "8000"},
            {"Bot4", "700"},
            {"Bot5", "60"},
            {"Bot6", "50"},
            {"Bot7", "40"},
            {"Bot8", "30"},
            {"Bot9", "20"},
            {"Bot10", "10"}
        };
        for (int i=0; i<10; i++) {
            fout << classifica[i][0] << ' ' << classifica[i][1] << endl;
            cout << classifica[i][0] << ' ' << classifica[i][1] << endl;
        }
        return;
    }

    // stampa i primi 10 risultati migliori con usernamme
    string classifica[10][2];
    for (int i=0; i<10; i++) {
        fin >> classifica[i][0]; // Nella prima colonna ci sono gli username
        fin >> classifica[i][1]; // Nella seconda colonna ci sono i punteggi sottoforma di stringa
        cout << classifica[i][0] << ' ' << classifica[i][1] << endl;
    }
}


void scriviDati(string username, int punteggio) 
{
    // Apro il file utenti.txt e inserisco in mezzo l'utente SE ha fatto un punteggio da classifica

    string classifica[10][2]; // Classifica, ma meglio dire elenco dei migliori 10 risultati

    ifstream fin;
    fin.open("utenti.txt", ios::in);

    for(int j=0;j<10;j++) {
        fin >> classifica[j][0];
        fin >> classifica[j][1];
    }
    if (punteggio < stoi(classifica[9][1])) // stoi = String TO Int
        return;

    ofstream fout;
    fout.open("utenti.txt", ios::out);
    
    // Inserisco il punteggio nella classifica
    for (int i=0; i<10; i++) {
        if (stoi(classifica[i][1])<punteggio) {
            fout << username << ' ' << to_string(punteggio) << endl;
            cout << username << ' ' << to_string(punteggio) << endl;
            for (int f=i+1; f<10; f++) {
                fout << classifica[f-1][0] << ' ' << classifica[f-1][1] << endl;
                cout << classifica[f-1][0] << ' ' << classifica[f-1][1] << endl;
            }
            break;
        } else {
            // Poi la ristampi nel file
            fout << classifica[i][0] << ' ' << classifica[i][1] << endl;
            cout << classifica[i][0] << ' ' << classifica[i][1] << endl;
        }
    }
    system("pause >nul");
}


int leggiRecord(string username) {
    // Se è già registrato fai return del suo record
    ifstream fin("utenti.txt", ios::in);
    string classifica[10][2];
    if (fin) {
		for (int j=0; j<10; j++) {
            fin >> classifica[j][0];
            fin >> classifica[j][1];
        }
        for (int j=0; j<10; j++) {
            if (classifica[j][0] == username)
                return stoi(classifica[j][1]);
        }
	}
    return 0; // Se non è ancora registrato fai return 0
}
