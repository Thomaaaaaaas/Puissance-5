#include "Player.h"

// constructeur
Player::Player(const string& n, char t, bool isComp, int difficulty) : name(n), token(t), isComputer(isComp), difficulty(difficulty) {}

string Player::getName() const {
    return name;
}

char Player::getToken() const {
    return token;//return le sympbole du token
}

bool Player::getIsComputer() const {
    return isComputer;//true si le joueur est un ordinateur
}

int Player::getDifficulty() const {
    return difficulty;
}

void Player::setDifficulty(int level) {
    difficulty = level;
}

void Player::setIsComputer(bool isComp) {
    isComputer = isComp;//modifie le statut du joueur, humain ou ordinateur
}

