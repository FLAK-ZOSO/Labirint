#include <iostream>
#include <fstream>
#include <string>
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
    }
    for (int i=0; i<10; i++)
        cout << classifica[i][0] << ' ' << classifica[i][1] << endl;
}


void scriviDati(string username, int punteggio) 
{
    // Apro il file utenti.txt e inserisco in mezzo l'utente SE ha fatto un punteggio da classifica

    string classifica[10][2];

    ifstream fin;
    fin.open("utenti.txt", ios::in);

    for(int j=0;j<10;j++) {
        fin >> classifica[j][0];
        fin >> classifica[j][1];
    }
    if (punteggio < stoi(classifica[9][1])) // stoi = String TO Int
        return;

    // Inserisco il punteggio nella classifica
    for (int i=0; i<10; i++)
    {
        if (stoi(classifica[i][1])<punteggio)
        {
            classifica[i][0]=username;
            classifica[i][1]=to_string(punteggio);
            for (int f=i+1; f<9; f++) {
                classifica[i+1][0]=classifica[i][0];
                classifica[i+1][1]=classifica[i][1];
            }               
        }
    }


    // Poi la ristampi nel file
    ofstream fout;
	fout.open("utenti.txt", ios::out);

	if (fout) {
		for (int i=0; i<10; i++)
            fout << classifica[i][0] << ' ' << classifica[i][1] << endl;
	}
    for (int i=0; i<10; i++)
        cout << classifica[i][0] << ' ' << classifica[i][1] << endl;
    system("pause");
}


int leggiRecord(string username) {
    // Se è già registrato fai return del suo record
    ifstream fin;
    fin.open("utenti.txt", ios::in);
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
