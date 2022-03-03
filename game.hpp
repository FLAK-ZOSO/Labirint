#include <iostream>
#include <cstdlib>
#include "time.h"
#include "cleanScreen.hpp"


struct Game {
    char matrix[20][50]; // Il campo di gioco
    int points; // Punteggio del giocatore
    std::string name; // Nome del giocatore
    char skin; // Iniziale del giocatore, da usare come pedina
    int position; // Posizione in orizzontale della pedina
    bool emptyLine; // Una riga su due sarà stampata vuota, quando è true si stampa una riga vuota
    int bonus; // Saranno messi dei bonus ogni 4 righe, quando il contatore è a 3 si mette un bonus
};


void updateMatrix(Game &game_) 
{
    

}


// Stampa la matrice (che si trova tra gli attributi di game_ a game_.matrix)
void printMatrix(Game game_) 
{   // Matrice di 20 righe e 50 colonne
    using namespace std;
    for(int r=0;r<20;r++) {
        for(int c=0;c<50;c++)
            cout<<matrix[r][c];
        cout<<endl;
    }
}


// Muove la pedina su comando dell'utente
void processMove(Game &game_, std::string mossa)
{
    // Se inserisce "d" oppure "D", la pedina si muove di 1 a destra
    // Se inserisce "s" oppure "S", la pedina si muove di 1 a sinistra
    if(mossa=='d'|| mossa=='D')
        game_.position++;
    if(mossa=='s'|| mossa=='S')
        game_.position--;
    // Quando dovrò assemblare la matrice farò qualcosa come:
    // game_.matrice[3][game_.position] = game_.skin;

    // Effetto pacman perché se no si asfalta contro i muri e dà errore
    /*
    ########
    #     F# -> Se la mossa è "d", si muove a destra, e viene teletrasportato alla destra del bordo sinistro
    #      #
    #      #
    ########
    */
    if(game.position>48)
        game_.position = 1;
    if(game.position<2)
        game_.position = 48;
}


// Return true se hai colpito una nuvola ('*'), altrimenti return false
bool checkMatrix(Game &game_) 
{
    /*
    ########
    #   A  # -> matrix[3][game_.position]
    #   *  # -> matrix[4][game_.position]
    #      #
    ########
    */
    if(matrix[4][game_.position]=='*')
        return true;
    return false;
}