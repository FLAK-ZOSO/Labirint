#include <future>
#include <thread>
#include "game.hpp"
#include "menu.hpp"


int game(std::string name) { // Ritorna il numero di punti
    Game myGame; // myGame è un'istanza della struct Game
    myGame.points = 0;
    myGame.bonus = 0;
    myGame.emptyLine = false;
    srand(time(0)); // Rende casuale i numeri generati da rand()

    // Riempio la matrice, che in partenza è vuota
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 50; j++)
            myGame.matrix[i][j] = ' ';
        myGame.matrix[i][0] = '#';
        myGame.matrix[i][49] = '#';
    }

    // Il personaggio del giocatore sarà la lettera maiuscola della sua iniziale
    myGame.name = name;
    myGame.skin = name[0];
    myGame.position = 9;
    myGame.matrix[3][24] = myGame.skin;    

    while (true) {
        // Enable standard literals as 2s and ""s
        using namespace std::literals;
    	// Esegue la funzione in modo asincrono
	    auto input = std::async(std::launch::async, [] {
	        char move;
	        if (std::cin >> move) 
                return move;
	    });
	    
        bool end = false;
        // Continue execution in main thread.
        while (input.wait_for(0.2s) != std::future_status::ready) {
            // Controlliamo se ha perso
            if (checkMatrix(myGame)) { // The user lost
                end = true;
                break;
            }
            
            // Aggiorniamo la matrice
            updateMatrix(myGame);

            // Aggiorniamo l'immagine
            printMatrix(myGame);

            // Aumentiamo i punti
            myGame.points++;
        }
        processMove(myGame, input.get());
        if (end)
            break;
    }
    updateMatrix(myGame);
    printMatrix(myGame);
	return myGame.points;
}


bool giocaAncora(string username) {
    system("cls");
    std::cout << "Do you want to play again? (y/n)\n> ";
    char answer;
    std::cin >> answer;
    return (answer == 'y' || answer == 'Y'); 
}


int main() {
    // Stampiamo il menu con una funzione che viene da menu.hpp
    stampaScrittaMenu();
    system("pause"); // Mette in pausa l'esecuzione finché l'utente non preme invio
    system("cls"); // Pulisce lo schermo

    // Elaboriamo tutti i dati con dei file .txt (di testo)
    stampaDati();
    system("pause");
    system("cls");

    // Chiediamo le varie informazioni all'utente
    std::string name;
    std::cout << "Username: ";
    std::cin >> name;

    // Leggi record se c'è
    int points, record = leggiRecord(name);

    do {
        points = game(name);
        std::cout << "You scored " << points << " points" << std::endl;
        std::cout << "Your record is " << record << " points" << std::endl;
        system("pause");
        system("cls");
        if (record < points) { // Se ha battuto il record personale
            std::cout << "Checking the leaderboard... " << std::endl;
            scriviDati(name, points); // Salva i dati nel file utenti.txt
        }
    } while (giocaAncora(name)); // Chiediamo se vuole rigiocare
    
    return 0;
}