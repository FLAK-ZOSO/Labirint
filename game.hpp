#include <iostream>
#include <cstdlib>
#include "time.h"


struct Game {
    char matrix[20][50]; // Il campo di gioco
    int points; // Punteggio del giocatore
    std::string name; // Nome del giocatore
    char skin; // Iniziale del giocatore, da usare come pedina
    int x; // Posizione in orizzontale della pedina
    int y; // Posizione in verticale della pedina
    bool z; // Posizione 3D della pedina, che ha solo due valori, true è il default
    unsigned zFrames; // Quanti frame può ancora passare con l'immunità
    unsigned zFuel; // Quante volte può ancora usare Z
    bool emptyLine; // Una riga su due sarà stampata vuota, quando è true si stampa una riga vuota
    unsigned maxCloudWidth; // Massima larghezza delle nuvole
    unsigned bonus; // Una riga su Game.bonusFrequency potrebbe contenere un bonus
    unsigned bonusFrequency; // Ogni quante righe appare un bonus
    unsigned borderCounter; // Contatore per l'array della lunghezza del bordo sinistro
};
const int bordersLen = 48;
unsigned short borders[bordersLen] = {
    7, 7,
    6, 6, 6,
    5, 5, 5, 5,
    4, 4, 4, 4, 4,
    3, 3, 3, 3,
    2, 2, 2,
    1, 1,
    0,
    1, 1,
    2, 2, 2,
    3, 3, 3, 3,
    4, 4, 4, 4, 4,
    5, 5, 5, 5,
    6, 6, 6,
    7, 7,
    8
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
        int cloudBeginning = (rand() % (34-(borders[game_.borderCounter]))) + 15 + (borders[game_.borderCounter]);
        int cloudWidth = rand() % game_.maxCloudWidth;
        int cloudEnd = cloudBeginning + cloudWidth;
        for (int i = cloudBeginning; i < cloudEnd+1; i++)
            newLine[i] = '*';
    } else {
        game_.emptyLine = true;
    }
    if (game_.bonus == game_.bonusFrequency) {
        game_.bonus = 0;
        int bonus = rand() % 34 + 15; // Bonus in quelle posizioni (0-15) sarebbero comunque coperti dai bordi
        newLine[bonus] = '$';
    } else {
        game_.bonus++;
    }
    if (rand()%15 == 0) // Una volta su 15 può capitare un "carburante z", il cui nome fa schifo ma shh
        newLine[rand()%34 + 15] = '@';
    int endLeftBorder = (borders[game_.borderCounter])+15;
    int beginRightBorder = 49-(30-endLeftBorder);
    for (int i = 1; i < endLeftBorder; i++)
        newLine[i] = '-';
    for (int i = beginRightBorder; i < 49; i++)
        newLine[i] = '-';
    newLine[0] = '#';
    newLine[49] = '#';
    for (int i = 0; i < 50; i++)
    	game_.matrix[19][i] = newLine[i];
    
    // Border
    if (game_.borderCounter == bordersLen-1) {
        game_.borderCounter = 0;
    } else {
        game_.borderCounter++;
    }

    if (game_.z) {
        game_.points++;
    } else {
        game_.points--;
        if (game_.zFrames > 0)
            game_.zFrames--;
        else
            game_.z = true;
    }
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
    std::cout << "X=" << game_.x << " Y=" << game_.y << " Z=" << game_.z << std::endl;
    std::cout << "Z Fuel: " << game_.zFuel << std::endl;
    if (!game_.z)
        std::cout << "Z Frames: " << game_.zFrames << std::endl;
}


void processMove(Game &game_, std::string input) {
    // Horizontal
    if (input == "s" || input == "S")
        game_.x--;
    if (input == "d" || input == "D")
        game_.x++;
    if (input == "ss" || input == "SS")
		game_.x -= 2;
    if (input == "dd" || input == "DD")
        game_.x += 2;
    // Vertical
    if (input == "a" || input == "A")
        game_.y--;
    if (input == "b" || input == "B")
        game_.y++;
    // 3D
    if (input == "z" || input == "Z") {
        if (game_.z) {
            if (game_.zFuel > 0) {
                game_.z = false;
                game_.zFuel--;
                game_.zFrames = 10;
            }
        } else {
            game_.z = true;
        }
    }

    // Effetto pacman verticale
    if (game_.y < 0)
        game_.y = 17;
    if (game_.y > 17)
        game_.y = 0;
}


bool checkMatrix(Game &game_) {
    if (game_.z) { // Se è sul piano di sopra
        if (game_.matrix[game_.y+1][game_.x] == '*')
            return true; // Il giocatore ha perso
    }
    if (game_.matrix[game_.y+1][game_.x] == '-')
            return true; // Il giocatore ha perso
    if (game_.matrix[game_.y+1][game_.x] == '$')
        game_.points += 10;
    if (game_.matrix[game_.y+1][game_.x] == '@') {
        game_.zFuel++;
    }
    return false;
}


bool newGame() {
    char answer;
    std::cout << "Play again? (y/n)" << std::endl << ">";
    std::cin >> answer;

    switch (answer) {
        case 'y': case 'Y':
            return true;
        case 'n': case 'N':
            return false;
        default:
            std::cout << "Invalid input" << std::endl;
            return false;
    }
}