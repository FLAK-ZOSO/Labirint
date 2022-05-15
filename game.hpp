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
    unsigned short zFrames; // Quanti frame può ancora passare con l'immunità
    unsigned short zFuel; // Quante volte può ancora usare Z
    bool emptyLine; // Una riga su due sarà stampata vuota, quando è true si stampa una riga vuota
    unsigned short maxCloudWidth; // Massima larghezza delle nuvole
    unsigned short bonus; // Una riga su Game.bonusFrequency potrebbe contenere un bonus
    unsigned short bonusFrequency; // Ogni quante righe appare un bonus
    unsigned short borderCounter; // Contatore per l'array della lunghezza del bordo sinistro
};
const unsigned short bordersLen = 48;
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


void processMove(Game &game_, char input) {
    // W/A/S/D (W = up, A = left, S = down, D = right)
    if (input == 'a' || input == 'A')
        game_.x--;
    if (input == 'd' || input == 'D')
        game_.x++;
    if (input == 'w' || input == 'W')
        game_.y--;
    if (input == 's' || input == 'S')
        game_.y++;

    if (input == 'z' || input == 'Z') { // Se clicchi 'z' o 'Z'
        if (game_.z) { // Se è già in Z...
            if (game_.zFuel > 0) { // Se hai ancora @ da usare
                game_.z = false; // Passa in modalità z
                game_.zFuel--; // Usa un @ (ti viene tolto)
                game_.zFrames = 10; // Ti dà 10 fotogrammi d'immunità
            }
        } else {
            game_.z = true; // Se hai cliccato z mentre stavi in modalità z, esci dalla modalità z
        }
    }

    // Effetto pacman verticale
    if (game_.y < 0) // Se urti il bordo superiore
        game_.y = 17; // Torna al bordo inferiore
    else if (game_.y > 17) // Se urti il bordo inferiore
        game_.y = 0; // Torna al bordo superiore
}


bool checkMatrix(Game &game_) {
    if (game_.z) { // Se non sei in modalità z...
        if (game_.matrix[game_.y+1][game_.x] == '*') // ...e da fesso colpisci una nuvola...
            return true; // ...perdi
    }
    if (game_.matrix[game_.y+1][game_.x] == '-') // Se da fesso colpisci una riga...
        return true; // ...perdi
    if (game_.matrix[game_.y+1][game_.x] == '$') // Se da bravo colpisci un bonus...
        game_.points += 10; // ...prendi punti
    if (game_.matrix[game_.y+1][game_.x] == '@') { // Se da bravo colpisci un carburante z...
        game_.zFuel++; // ...prendi un @
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