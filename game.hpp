#include <iostream>
#include <cstdlib>
#include "time.h"
#include "cleanScreen.hpp"


struct Game {
    char matrix[20][50]; // Il campo di gioco
    unsigned points; // Punteggio del giocatore (unsigned = int ma senza i negativi)
    std::string name; // Nome del giocatore
    char skin; // Iniziale del giocatore, da usare come pedina
    unsigned position; // Posizione in orizzontale della pedina
    bool emptyLine; // Una riga su due sarà stampata vuota, quando è true si stampa una riga vuota
    unsigned bonus; // Saranno messi dei bonus ogni 5 righe, quando il contatore è a 4 si mette un bonus
};


void updateMatrix(Game &game_) {
    // Scaliamo tutto di una riga
    for (int i = 1; i < 20; i++) {
    	for (int j = 0; j < 50; j++)
        	game_.matrix[i-1][j] = game_.matrix[i][j];
    }

    // Trasformiamo la pedina vecchia in uno spazio
    for (int i = 0; i < 50; i++) {
        if (game_.matrix[2][i] == game_.skin) {
            game_.matrix[2][i] = ' ';
            break;
        }
    }
    game_.matrix[3][game_.position] = game_.skin;

    // Generiamo casualmente la nuova riga
    char newLine[50];
    for (int i = 0; i < 50; i++)
        newLine[i] = ' ';
    int cloudBeginning = rand() % 49;
    int cloudWidth = rand() % 5;
    int cloudEnd = cloudBeginning + cloudWidth;
    for (int i = cloudBeginning; i < cloudEnd+1; i++)
        newLine[i] = '*';
    newLine[0] = '#';
    newLine[49] = '#';
    for (int i = 0; i < 50; i++)
    	game_.matrix[19][i] = newLine[i];

    game_.points++;
}


void printMatrix(Game game_) {
    system("cls");
    
    // Stampo la matrice
    for (int i = 0; i < 50; i++)
        std::cout << '#';
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 50; j++)
            std::cout << game_.matrix[i][j];
        std::cout << std::endl;
    }
    for (int i = 0; i < 50; i++)
        std::cout << '#';
    std::cout << std::endl << game_.points << std::endl;
}


void processMove(Game &game_, std::string input) {
    if (input == "s" or input == "S")
        game_.position--;
    if (input == "d" or input == "D")
        game_.position++;
    if (input == "ss" or input == "SS")
		game_.position -= 2;
    if (input == "dd" or input == "DD")
        game_.position += 2;

    if (game_.position < 0)
        game_.position = 1;
    if (game_.position > 48)
        game_.position = 48;
}


bool checkMatrix(Game game_) {
    if (game_.matrix[4][game_.position] == '*')
        return true; // Il giocatore ha perso
    if (game_.matrix[4][game_.position] == '$')
        game_.points += 10;
    return false;
}