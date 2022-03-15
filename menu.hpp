int main()
{
        ifstream fin;
        string testo;
        int numero;
        int arr[20];
        int conta=0;
        
        fin.open ("prova.txt", ios::in);
        //se apertura file va a buon fine fin è diverso da zero
        
        if (fin!=0)
        {
                //getline restituisce zero quando trova EOF (end of file)
                while (getline (fin, testo)!=0) 
                {
                          arr[conta]=stoi(testo);
                          conta++;
                }
                
                for (int i=0;i<conta;i++)
                        cout << arr[i] << endl;
                
                //getline(fin,testo);
                //cout << testo;
        }
        else
                cout << "errore apertura file prova.txt" << endl;
        
        fin.close();
}
