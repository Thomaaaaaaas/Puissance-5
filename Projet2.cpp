#include "Game.h" 

// Fonction pour nettoyer les entrées précédentes dans le tampon
void clearCin() {
    cin.clear(); // Réinitialise les flags d'erreur de cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore le reste de la ligne courante
}

// Fonction pour lire un token de manière sécurisée
char readToken(const string& playerName) {
    char token;
    cout << playerName << ", Choississez votre pion (X ou O): ";
    cin >> token;
    clearCin(); 
    return token;
}

bool isValidNumber(const string& str) {
    // Vérifie si la chaîne est un nombre entier positif
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }
    return !str.empty() && stoi(str) > 0;
}

int getValidNumber(const string& prompt) {
    string input;
    int validNumber = 0;
    bool inputIsValid = false;

    do {
        cout << prompt;
        getline(cin, input);

        if (isValidNumber(input)) {
            validNumber = stoi(input);// Convertit la chaîne en nombre entier
            inputIsValid = true;
        }
        else {
            cout << "Erreur. Entrez un entier positif.\n";
        }
    } while (!inputIsValid);

    return validNumber;
}

int main() {
    string name1, name2;
    char token1, token2;

    int rows = getValidNumber("Entrez le nombre de lignes: ");
    int cols = getValidNumber("Entrez le nombre de colonnes: ");

    cout << "Entrez le nom du Player 1: ";
    getline(cin, name1);
    token1 = readToken(name1);

    cout << "Entrez le nom du Player 2: ";
    getline(cin, name2);
    token2 = readToken(name2);

    // Vérifie que les deux joueurs n'ont pas choisi le même symbole
    while (token1 == token2) {
        cout << "Vous avez choisis le même pion.\n";
        token2 = readToken(name2);
    }

    Player player1("Player 1", 'X', false);// Création de joueur
    Player player2("Player 2", 'O', false); 

    Game game(rows, cols, player1, player2);// Initialisation du jeu
    game.play();// Lancement
    return 0;
}
