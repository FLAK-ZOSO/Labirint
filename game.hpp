#include <iostream>
#include "cleanScreen.hpp"


struct Game {
    char matrix[50][80]; // Il campo di gioco
    unsigned points; // Punteggio del giocatore (unsigned = int ma senza i negativi)
    std::string name; // Nome del giocatore
    char skin; // Iniziale del giocatore, da usare come pedina
    unsigned position; // Posizione in orizzontale della pedina
    bool emptyLine; // Una riga su due sarà stampata vuota, quando è true si stampa una riga vuota
    unsigned bonus; // Saranno messi dei bonus ogni 5 righe, quando il contatore è a 4 si mette un bonus
};


void updateMatrix(Game game_) {
    // Scaliamo tutto di una riga
    for (int i = 1; i < 50; i++) {
    	for (int j = 0; j < 80; j++)
        	game_.matrix[i-1][j] = game_.matrix[i][j];
    }

    // Trasformiamo la pedina vecchia in uno spazio
    for (int i = 0; i < 80; i++) {
        if (game_.matrix[23][i] == game_.skin) {
            game_.matrix[23][i] = '-';
            break;
        }
    }

    // Generiamo casualmente la nuova riga
    char newLine[80];
    for (int i = 0; i < 80; i++)
        newLine[i] = '-';
    for (int i = 0; i < 80; i++)
    	game_.matrix[49][i] = newLine[i];

    game_.points++;
}


void printMatrix(Game game_) {
    system("cls");
    
    // Stampo la matrice
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 80; j++)
            std::cout << game_.matrix[i][j];
        std::cout << std::endl;
    }
}


void processMove(Game game_, std::string input) {
    if (input == "s" or input == "S")
        game_.position--;
    if (input == "d" or input == "D")
        game_.position++;
    if (input == "ss" or input == "SS")
		game_.position -= 2;
    if (input == "dd" or input == "DD")
        game_.position += 2;

    if (game_.position < 0)
        game_.position = 0;
    if (game_.position > 79)
        game_.position = 79;
}


bool checkMatrix(Game game_) {
    if (game_.matrix[25][game_.position] == 'X')
        return true; // Il giocatore ha perso
    if (game_.matrix[25][game_.position] == '$')
        game_.points += 10;
    return false;
}