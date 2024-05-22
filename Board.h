#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
using namespace std;

class Board {
    int rows, cols;
    vector<vector<char>> grid;//grille de jeu

public:
    Board(int r, int c);
    void display() const;//affiche le plateau dans la console
    bool placeToken(int col, char token);
    bool checkWinner(char token) const;
    bool checkLine(int startRow, int startCol, int dRow, int dCol, char token) const;//verifie une ligne si elle contient une serie de jeton gagnante
    void clear();
    bool removeToken(int col);
    bool isGameOver() const;
    int getRows() const;//nombre de lignes
    int getCols() const;//nombre de colonnes
    char getCell(int row, int col) const;//contenu d'une celulle de la grille
    bool canPlaceToken(int col) const;

};

#endif // BOARD_H
