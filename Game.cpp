#include "Game.h"
#include "Board.h"


Game::Game(int rows, int cols, const Player& p1, const Player& p2)
    : board(rows, cols), players{ p1, p2 }, currentPlayer(0), difficulty(0) {}

void Game::switchPlayer() {
    currentPlayer = 1 - currentPlayer;
}


void Game::play() {
    cout << "Choisissez le mode de jeu :\n";
    cout << "1. Joueur contre Joueur\n";
    cout << "2. Joueur contre IA Faible\n";
    cout << "3. Joueur contre IA Forte\n";
    int mode;
    cin >> mode;

    // Configurez les joueurs selon le mode choisi
    switch (mode) {
    case 1:
        players[1].setIsComputer(false);
        break;
    case 2:
        players[1].setIsComputer(true);
        players[1].setDifficulty(1);  // Niveau faible
        break;
    case 3:
        players[1].setIsComputer(true);
        players[1].setDifficulty(2);  // Niveau fort
        break;
    default:
        cout << "Mode invalide, par défaut Joueur contre Joueur sera sélectionné.\n";
        players[1].setIsComputer(false);
    }

    char choice;

    do {
        board.clear();  // Nettoie le plateau pour une nouvelle partie
        currentPlayer = 0;  // Commence par le joueur humain

        while (!board.isGameOver()) {
            board.display();  // Affiche le plateau

            if (!players[currentPlayer].getIsComputer()) {
                // Tour du joueur humain
                cout << players[currentPlayer].getName() << " (" << players[currentPlayer].getToken() << "), Entrez votre colonne: ";
                int col;
                cin >> col;  // Le joueur humain choisit une colonne
                if (board.placeToken(col, players[currentPlayer].getToken())) {
                    if (board.checkWinner(players[currentPlayer].getToken())) {
                        board.display();
                        cout << players[currentPlayer].getName() << " a gagne!\n";
                        break;
                    }
                    switchPlayer();
                }
                else {
                    cout << "Colonne pleine ou invalide. Reessayez.\n";
                }
            }
            else {
                // Tour de l'IA
                int col = -1;
                if (players[currentPlayer].getDifficulty() == 1) {  // IA faible
                    do {
                        col = rand() % board.getCols(); // Choix aléatoire de la colonne
                    } while (!board.placeToken(col, players[currentPlayer].getToken()) && !board.isGameOver());
                }
                else if (players[currentPlayer].getDifficulty() == 2) {  // IA forte
                    col = getBestMove(players[currentPlayer].getToken());// Appel de getBestMove pour faire le meilleur choix
                    if (col != -1) {
                        board.placeToken(col, players[currentPlayer].getToken());
                    }
                }

                if (col != -1) {
                    board.display();  // Affiche le coup de l'IA
                    cout << "L IA a joue a la colonne " << col << "\n";
                    if (board.checkWinner(players[currentPlayer].getToken())) {
                        cout << "L IA a gagne!\n";
                        break;
                    }
                    switchPlayer();
                }
                else {
                    cout << "Aucun coup valide pour l IA.\n";
                }
            }
        }

        cout << "Voulez-vous jouer une autre partie? (O/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice == 'O' || choice == 'o');
}


//Méthode pour trouver le meilleur coup
int Game::getBestMove(char token) {
    int bestScore = numeric_limits<int>::min();
    int bestCol = -1;
    for (int col = 0; col < board.getCols(); ++col) {
        if (board.canPlaceToken(col)) {  
            board.placeToken(col, token);
            int score = minimax(4, numeric_limits<int>::min(), numeric_limits<int>::max(), false, token);
            board.removeToken(col);
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    return bestCol;  // Retourne -1 si aucune colonne valide n'est trouvée
}


int Game::minimax(int depth, int alpha, int beta, bool maximizingPlayer, char token) {
    // Base case: Si la profondeur est 0 ou le jeu est terminé (victoire ou nul)
    if (depth == 0 || board.isGameOver()) {
        return evaluateBoard(token);  // Évaluation du plateau actuel
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();  // Initialiser à l'infini négatif
        for (int col = 0; col < board.getCols(); ++col) {
            if (board.placeToken(col, token)) {  // Si le jeton peut être placé dans la colonne
                int eval = minimax(depth - 1, alpha, beta, false, token == 'X' ? 'O' : 'X'); // Prochain appel Minimax pour l'adversaire
                board.removeToken(col);  // Retirer le jeton pour restaurer l'état du plateau
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) {
                    break;  // Élagage Beta
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = numeric_limits<int>::max();  // Initialiser à l'infini positif
        for (int col = 0; col < board.getCols(); ++col) {
            if (board.placeToken(col, token)) {
                int eval = minimax(depth - 1, alpha, beta, true, token == 'X' ? 'O' : 'X');
                board.removeToken(col);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) {
                    break;  // Élagage Alpha
                }
            }
        }
        return minEval;
    }
}



int Game::evaluateBoard(char token) {
    int score = 0;
    for (int row = 0; row < board.getRows(); ++row) {
        for (int col = 0; col < board.getCols(); ++col) {
            score += evaluatePosition(row, col, token);  // Appel de evaluatePosition ici
        }
    }
    return score;
}

int Game::evaluatePosition(int row, int col, char token) {
    int score = 0;
    int count = 0;

    // Directions à vérifier: horizontale, verticale, diagonale descendante, diagonale montante
    int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {-1, 1} };
    int lineLength = 5;  // Longueur nécessaire pour gagner

    for (auto& dir : directions) {
        count = 1;  // Compter le jeton actuel
        // Vérifier dans la direction positive
        for (int i = 1; i < lineLength; i++) {
            int newRow = row + i * dir[0];
            int newCol = col + i * dir[1];
            if (newRow >= 0 && newRow < board.getRows() && newCol >= 0 && newCol < board.getCols() && board.getCell(newRow, newCol) == token) {
                count++;
            }
            else {
                break;
            }
        }
        // Vérifier dans la direction négative
        for (int i = 1; i < lineLength; i++) {
            int newRow = row - i * dir[0];
            int newCol = col - i * dir[1];
            if (newRow >= 0 && newRow < board.getRows() && newCol >= 0 && newCol < board.getCols() && board.getCell(newRow, newCol) == token) {
                count++;
            }
            else {
                break;
            }
        }
        // Calcule le score basé sur le nombre de jetons alignés
        if (count >= lineLength) {
            score += 1000;  // Score élevé pour une victoire possible
        }
        else if (count == lineLength - 1) {
            score += 100;  // Score moindre pour une approche de victoire
        }
        else if (count == lineLength - 2) {
            score += 10;
        }
        else if (count >= 2) {
            score += count;  // Donner un petit score pour au moins deux jetons alignés
        }
    }

    return score;
}


void Game::setDifficulty(int level) {
    if (level >= 0 && level <= 2) {  
        difficulty = level;
        players[1].setIsComputer(level > 0);  // Si level > 0, le joueur 2 est une IA
        players[1].setDifficulty(level);  // Transmet la difficulté à l'objet Player
    }
    else {
        std::cout << "Niveau de difficulté non valide. Choisissez 0 (Pas d'IA), 1 (IA Faible) ou 2 (IA Forte).\n";
    }
}
