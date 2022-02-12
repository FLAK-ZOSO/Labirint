#include <future>
#include <thread>
#include "game.hpp"


int game(std::string name) { // Ritorna il numero di punti
    Game myGame;
    myGame.points = 0;
    myGame.bonus = 0;
    myGame.emptyLine = false;
    myGame.borderCounter = 0;
    srand(time(0));

    // Informazioni
    std::cout << "Bonus frequency: ";
    std::cin >> myGame.bonusFrequency;
    std::cout << "Cloud max width: ";
    std::cin >> myGame.maxCloudWidth;
    if (myGame.maxCloudWidth > 10)
        myGame.maxCloudWidth = 10;

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
    myGame.x = 24;
    myGame.y = 3;
    myGame.matrix[3][24] = myGame.skin;    

    bool end = false;
    while (true) {
        // Enable standard literals as 2s and ""s.
        using namespace std::literals;
    	// Execute lambda asyncronously.
	    auto input = std::async(std::launch::async, [] {
	        std::string move;
	        if (std::cin >> move) return move;
	    });
	    
        // Continue execution in main thread.
        while (input.wait_for(0.3s) != std::future_status::ready) {
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
        if (end) break;
    }
    updateMatrix(myGame);
    printMatrix(myGame);
    std::cout << "You lost... " << std::endl;
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