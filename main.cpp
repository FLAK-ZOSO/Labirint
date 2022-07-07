#include <future>
#include <thread>
#include <limits>
#include <cstring>
#include <conio.h>

// Puoi includere file creati da te, scritti in C++ 
// ...ma con estensione .hpp invece che .cpp
#include "game.hpp" // Questo file è stato creato da noi
#include "menu.hpp" // Questo file è stato creato da Asia
// g++ main.cpp -o labirint.exe -std=c++2a


char inputMove() {
	char move = getch();
    return move;
}


Game game(std::string name) { // Ritorna l'oggetto Game
    Game myGame;
    myGame.points = 0;
    myGame.bonus = 0;
    myGame.emptyLine = false;
    myGame.borderCounter = 0;
    myGame.z = true; // true quando è il default
    myGame.zFrames = 0;
    myGame.zFuel = 0; // Quante @ devi ancora usare
    srand(time(0)); // Rende casuale la generazione di numeri casuali con rand()
    // std::ios_base::sync_with_stdio(false); // Rende la console non bloccante

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
    long double frame_duration_; // durata di un fotogramma in secondi
    while ((std::cout << "Duration of a frame: ") && (!(std::cin >> frame_duration_))) {
        std::cout << "Not a positive number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (myGame.bonusFrequency > 10)
        myGame.bonusFrequency = 10;
    if (myGame.bonusFrequency < 1)
        myGame.bonusFrequency = 1;
    if (myGame.maxCloudWidth > 15)
        myGame.maxCloudWidth = 15;
    if (frame_duration_ < 0.05)
        frame_duration_ = 0.05;

    // Variabile di tipo std::chrono che indica la durata del fotogramma
    auto frame_duration = std::chrono::duration<long double> (frame_duration_);

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
    if (color == "gray")
        system("color 70");
    if (color == "bordeaux")
        system("color 4E");

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

    bool end = false; // Variabile che serve a uscire dai while annidati
    while (!end) { // "while not end" = finché end è false
        // Enable standard literals as 2s and ""s.
        using namespace std::literals;
    	// Eseguo la funzione inputMove in modo asincrono
	    auto input = std::async(std::launch::async, inputMove);

        // Continue execution in main thread
        while (input.wait_for(frame_duration) != std::future_status::ready) {
            if (checkMatrix(myGame)) { // Controlliamo se ha perso
                end = true;
                break;
            }
            updateMatrix(myGame); // Aggiorniamo la matrice
            printMatrix(myGame); // Aggiorniamo l'immagine
        }
        processMove(myGame, input.get());
        printMatrix(myGame);
    }
    updateMatrix(myGame);
    printMatrix(myGame);
	return myGame;
}


bool giocaAncora(string username) {
    system("cls");
    std::cout << "Do you want to play again? (y/n)" << std::endl << "> ";
    char answer;
    std::cin >> answer;
    // Quindi fa return true se l'utente vuole giocare ancora
    return (answer == 'y' || answer == 'Y');
}


int main() {
    // Stampiamo il menu con una funzione che viene da menu.hpp
    stampaScrittaMenu();
    system("pause >nul"); // Mette in pausa l'esecuzione finché l'utente non preme invio
    system("cls"); // Pulisce lo schermo

    // Stampiamo tutti i dati con dei file .txt (di testo)
    stampaDati();
    system("pause >nul");
    system("cls");

    // Chiediamo le varie informazioni all'utente
    std::string name;
    std::cout << "Username: ";
    std::cin >> name;

    // Leggi record se c'è
    int points, record = leggiRecord(name);

    do {
        points = game(name).points;
        std::cout << "You scored " << points << " points" << std::endl;
        std::cout << "Your record is " << record << " points" << std::endl;
        system("pause >nul");
        system("cls");
        if (record < points) { // Se ha battuto il record personale
            std::cout << "Checking the leaderboard... " << std::endl;
            scriviDati(name, points); // Salva i dati nel file utenti.txt
        }
    } while (giocaAncora(name)); // Chiediamo se vuole rigiocare

    return 0;
}