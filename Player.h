#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
    string name;
    char token;
    bool isComputer; // Indique si le joueur est un ordinateur
    int difficulty;

public:
    Player(const string& name, char token, bool isComputer = false, int difficulty = 0);
    string getName() const;
    char getToken() const;
    bool getIsComputer() const; //return true si le joueur est un ordinateur
    void setIsComputer(bool isComp);//definit si le joueur est controlé par l'ordinateur
    int getDifficulty() const;//return le niveau de difficulté
    void setDifficulty(int level);//definit le niveau de difficulté
};

#endif // PLAYER_H
