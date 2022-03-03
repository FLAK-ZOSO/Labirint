#include <future>
#include <thread>
#include "game.hpp"


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
        }
        processMove(myGame, input.get());
        if (end)
            break;
    }
    updateMatrix(myGame);
    printMatrix(myGame);
    std::cout << "You lost... ";
	return myGame.points;
}


int main() {
    // Chiediamo le varie informazioni all'utente
    std::string name;
    std::cin >> name;
    // Salviamo tutti i dati in dei file .txt (di testo)

    while (true) {
        int points = game(name);

        // Chiediamo se vuole rigiocare
    }
    
    return 0;
}