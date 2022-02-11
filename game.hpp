#include <iostream>
#include <cstdlib>
#include "time.h"
#include "cleanScreen.hpp"


struct Game {
    char matrix[20][50]; // Il campo di gioco
    unsigned points; // Punteggio del giocatore (unsigned = int ma senza i negativi)
    std::string name; // Nome del giocatore
    char skin; // Iniziale del giocatore, da usare come pedina
    int x; // Posizione in orizzontale della pedina
    int y; // Posizione in verticale della pedina
    bool emptyLine; // Una riga su due sarà stampata vuota, quando è true si stampa una riga vuota
    unsigned bonus; // Saranno messi dei bonus ogni 4 righe, quando il contatore è a 3 si mette un bonus
};


void updateMatrix(Game &game_) {
    // Scaliamo tutto di una riga
    for (int i = 1; i < 20; i++) {
    	for (int j = 0; j < 50; j++)
        	game_.matrix[i-1][j] = game_.matrix[i][j];
    }

    // Trasformiamo la pedina vecchia in uno spazio
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 20; j++) {
            if (game_.matrix[j][i] == game_.skin) {
                game_.matrix[j][i] = ' ';
                break;
            }
        }
    }
    game_.matrix[game_.y][game_.x] = game_.skin;

    // Generiamo casualmente la nuova riga
    char newLine[50];
    for (int i = 0; i < 50; i++)
        newLine[i] = ' ';
    if (game_.emptyLine) {
        game_.emptyLine = false;
        int cloudBeginning = rand() % 49;
        int cloudWidth = rand() % 5;
        int cloudEnd = cloudBeginning + cloudWidth;
        for (int i = cloudBeginning; i < cloudEnd+1; i++)
            newLine[i] = '*';
    } else {
        game_.emptyLine = true;
    }
    if (game_.bonus == 3) {
        game_.bonus = 0;
        int bonus = rand() % 48;
        newLine[bonus+1] = '$';
    } else {
        game_.bonus++;
    }
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
    // Horizontal
    if (input == "s" or input == "S")
        game_.x--;
    if (input == "d" or input == "D")
        game_.x++;
    if (input == "ss" or input == "SS")
		game_.x -= 2;
    if (input == "dd" or input == "DD")
        game_.x += 2;

    // Vertical
    if (input == "a" or input == "A")
        game_.y--;
    if (input == "b" or input == "B")
        game_.y++;

    // Effetto pacman orizzontale
    if (game_.x <= 0)
        game_.x = 48;
    if (game_.x > 48)
        game_.x = 1;
    // Effetto pacman verticale
    if (game_.y <= 0)
        game_.y = 17;
    if (game_.y > 17)
        game_.y = 1;
}


bool checkMatrix(Game &game_) {
    if (game_.matrix[game_.y+1][game_.x] == '*')
        return true; // Il giocatore ha perso
    if (game_.matrix[game_.y+1][game_.x] == '$')
        game_.points += 10;
    return false;
}