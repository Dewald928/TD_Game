#ifndef PLAYER1_H
#define PLAYER1_H


class Player1
{
public:
    //player constructor
    Player1();

    //player member functions
    //getters
    int getGold();
    int getLives();
    int getIncome();

    //setters
    void setGold(int gold);
    void setLives(int lives);
    void setIncome(int income);

    //player attributes
    int Gold;
    int Lives;
    int Income;

};

#endif // PLAYER1_H
