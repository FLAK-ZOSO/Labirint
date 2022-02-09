#include <future>
#include <thread>
#include "game.hpp"


int game(std::string name) { // Ritorna il numero di punti
    Game myGame;

    // Riempio la matrice, che in partenza è vuota
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 80; j++)
            myGame.matrix[i][j] = '-';
    }

    // Il personaggio del giocatore sarà la lettera maiuscola della sua iniziale
    myGame.name = name;
    myGame.skin = name[0];
    myGame.position = 39;
    myGame.matrix[24][39] = myGame.skin;

    // Enable standard literals as 2s and ""s.
    using namespace std::literals;

    // Execute lambda asyncronously.
    auto f = std::async(std::launch::async, [] {
        std::string move;
        if (std::cin >> move) return move;
    });

    while (true) {
        // Continue execution in main thread.
        while (f.wait_for(0.5s) != std::future_status::ready) {
            // Controlliamo se ha perso
            if (checkMatrix(myGame)) { // The user lost
                goto end;
            }
            
            // Aggiorniamo la matrice
            updateMatrix(myGame);

            // Aggiorniamo l'immagine
            printMatrix(myGame);
        }
        processMove(myGame, f.get());
    }
    end:
    int x;
    std::cin >> x;
}


int main() {
    // Chiediamo le varie informazioni all'utente
    // Salviamo tutti i dati in dei file .txt (di testo)

    while (true) {
        game("Ciao");

        // Diciamo quanti punti ha fatto

        // Chiediamo se vuole rigiocare
    }
}