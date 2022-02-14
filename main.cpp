#include <future>
#include <thread>
#include <limits>
#include "game.hpp"


Game game(std::string name) { // Ritorna l'oggetto Game
    Game myGame;
    myGame.points = 0;
    myGame.bonus = 0;
    myGame.emptyLine = false;
    myGame.borderCounter = 0;
    myGame.z = true;
    srand(time(0));

    // Informazioni
    while ((std::cout << "Bonus frequency (period): ") && (!(std::cin >> myGame.bonusFrequency))) {
        std::cout << "Not a positive number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while ((std::cout << "Cloud max width: ") && (!(std::cin >> myGame.maxCloudWidth))) {
        std::cout << "Not a positive number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (myGame.bonusFrequency > 10)
        myGame.bonusFrequency = 10;
    if (myGame.maxCloudWidth > 10)
        myGame.maxCloudWidth = 10;

    // Colore
    std::string color;
    std::cout << "Color: ";
    std::cin >> color;
    if (color == "matrix")
        system("color 0A");
    if (color == "red")
        system("color 0C");
    if (color == "fucsia")
        system("color DE");

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
	return myGame;
}


int main() {
    // Chiediamo le varie informazioni all'utente
    std::string name;
    std::cout << "Username: ";
    std::cin >> name;

    // Salviamo tutti i dati in dei file .txt (di testo)

    while (true) {
        Game game_ = game(name);
        system("cls");
        std::cout << "Points: " << game_.points << std::endl;
        std::cout << "Difficulty multiplier: " <<  (game_.bonusFrequency+1) * game_.maxCloudWidth << std::endl;
        std::cout << "Score: " << game_.points * (game_.bonusFrequency+1) * game_.maxCloudWidth;
        std::cout << std::endl << std::endl;

        // Salviamo questi dati nel file di testo

        // Chiediamo se vuole rigiocare
        if (!newGame()) break;
    }
    // Menu principale
    
    return 0;
}