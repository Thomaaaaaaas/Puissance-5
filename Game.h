#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <vector>
#include <limits>
using namespace std;

class Game {
    Board board;
    Player players[2];
    int currentPlayer;
    int difficulty;

public:
    Game(int rows, int cols, const Player& p1, const Player& p2);
    void switchPlayer();
    void play();  
    int minimax(int depth, int alpha, int beta, bool maximizingPlayer, char token); 
    int evaluatePosition(int row, int col, char token);  // Évalue la position pour le Minimax
    int getBestMove(char token);  // Obtient le meilleur mouvement en utilisant l'algorithme Minimax
    int evaluateBoard(char token);  // Évalue le plateau pour le Minimax
    void setDifficulty(int level);
};

#endif // GAME_H
