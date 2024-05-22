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
    void setIsComputer(bool isComp);//definit si le joueur est control� par l'ordinateur
    int getDifficulty() const;//return le niveau de difficult�
    void setDifficulty(int level);//definit le niveau de difficult�
};

#endif // PLAYER_H
