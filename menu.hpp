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
        cout << "Errore apertura file utenti.txt" << endl;
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
    if (/*Il punteggio non è da top-10*/)
        return; // Se il punteggio non è da top 10 allora finisci la funzione perché il file non va modificato


    // Poi la ristampi nel file
    ofstream fout;
	fout.open("utenti.txt", ios::out);

	if (fout)
	{
		for(int i=0;i<10;i++)
        {       
            if(classifica[i][1]<punteggio)
                {
                 classifica[i][1]=punteggio;
                for(int f=i+1;f<10;f++)
                classifica[i][1]=classifica[i+1][1];
                                
                } // Eh già 😐
                
	}
        
	fout.close();
}


int leggiRecord(string username) {
    // Se è già registrato fai return del suo record
ifstream fin;
    fin.open("utenti.txt", ios::in);
    if (fout)
	{
		for(int i=0;i<10;i++)
        {       
            if(classifica[i][0]==personaggio)
                { if(classifica[i][1]<punteggio)
                 classifica[i][1]=punteggio;          
                } 
                
	}
        else 
        return 0;
        
        
	fout.close();

    // Se non è ancora registrato fai return 0
}