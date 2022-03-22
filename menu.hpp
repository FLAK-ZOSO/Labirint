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
            {"Bot1", "100000"}
            {"Bot2", "90000"}
            {"Bot3", "80000"}
            {"Bot4", "70000"}
            {"Bot5", "60000"}
            {"Bot6", "50000"}
            {"Bot7", "40000"}
            {"Bot8", "30000"}
            {"Bot9", "20000"}
            {"Bot10", "10000"}
        }
        for (int i=0; i<10; i++) {
            fout << classifica[i][0];
            fout << classifica[i][1];
            fout << endl;
        }
        for (int i=0; i<10; i++)
        cout << classifica[i][0]  < ' ' << classifica[i][1] << endl;
        system("pause");
        return;
    }

    // stampa i primi 10 risultati migliori con usernamme
    string classifica[10][2];
    for (int i=0; i<10; i++) {
        fin >> classifica[i][0]; // Nella prima colonna ci sono gli username
        fin >> classifica[i][1]; // Nella seconda colonna ci sono i punteggi sottoforma di stringa
    }
    for (int i=0; i<10; i++)
        cout << classifica[i][0]  < ' ' << classifica[i][1] << endl;
    
    fin.close();
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
    if (punteggio<stoi(classifica[10][2])) // stoi = String TO Int
        return 0;


    // Poi la ristampi nel file
    ofstream fout;
	fout.open("utenti.txt", ios::out);

	if (fout)
	{
		for (int i=0; i<10; i++)
        {
            if (stoi(classifica[i][1])<punteggio)
            {
                classifica[i][1]=to_string(punteggio);
                for (int f=i+1; f<9; f++)
                    classifica[i+1][1]=classifica[i][1];               
            } // Eh già 😐
        }
	}

	fout.close();
}


int leggiRecord(string username) {
    // Se è già registrato fai return del suo record
    ifstream fin;
    fin.open("utenti.txt", ios::in);
    if (fin)
	{
		for (int j=0; j<10; j++) {
            fin >> classifica[j][0];
            fin >> classifica[j][1];
        }
        for(int j=0;j<10;j++) {
            if (classifica[i][0] == username)
                return stoi(classifica[i][1]);
        }
        return 0;
	}
    else 
        return 0;
        
        
	fout.close();

    // Se non è ancora registrato fai return 0
}
