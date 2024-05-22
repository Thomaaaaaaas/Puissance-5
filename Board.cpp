#include "Board.h"

//constructeur
Board::Board(int r, int c) : rows(r), cols(c), grid(r, vector<char>(c, '.')) {}

//affichage du plateau sur la console
void Board::display() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << "\n";
    }
}

//placement des jetons
bool Board::placeToken(int col, char token) {
    if (col >= 0 && col < cols) {
        for (int i = rows - 1; i >= 0; --i) {
            if (grid[i][col] == '.') {
                grid[i][col] = token;
                return true;
            }
        }
    }
    return false;
}


bool Board::checkWinner(char token) const {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col] == token) {
                if (checkLine(row, col, 0, 1, token) ||  // Horizontale
                    checkLine(row, col, 1, 0, token) ||  // Verticale
                    checkLine(row, col, 1, 1, token) ||  // Diagonael descendant
                    checkLine(row, col, -1, 1, token)) { // Diagonale ascendant
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::checkLine(int startRow, int startCol, int dRow, int dCol, char token) const {
    int count = 0;
    int r = startRow, c = startCol;
    while (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == token) {
        count++;
        r += dRow;
        c += dCol;
    }
    return count >= 5;//si 5 jetons sont alignés
}

// reset du plateau
void Board::clear() {
    for (auto& row : grid) {
        fill(row.begin(), row.end(), '.');// remplissage de case vide
    }
}

bool Board::isGameOver() const {
    // verifie si X ou O a gagné
    if (checkWinner('X') || checkWinner('O')) return true;

    // verifie si le plateau est plein
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == '.') return false; // si une case vide est trouvée le jeu est pas terminé
        }
    }
    return true; // le plateau est plein personne gagne
}

bool Board::removeToken(int col) {
    for (int row = 0; row < rows; row++) {
        if (grid[row][col] != '.') {
            grid[row][col] = '.';
            return true;
        }
    }
    return false; // si deja vide
}

int Board::getRows() const {
    return rows; //return nombre de lignes
}

int Board::getCols() const {
    return cols; //return nombre de colonnes
}

char Board::getCell(int row, int col) const {
    return grid[row][col]; // return le contenu de la cellule
}


bool Board::canPlaceToken(int col) const {
    if (col < 0 || col >= cols) return false;  // verifie que la colonne est valide
    return grid[0][col] == '.';  // verifie sur la case superieur l'est aussi
}




