#include "player1.h"

Player1::Player1()
{
    Gold = 1000;
    Lives = 30;
    Income = 200; //gold per turn
}

int Player1::getGold()
{
    return Gold;
}

int Player1::getLives()
{
    return Lives;
}

int Player1::getIncome()
{
    return Income;
}

void Player1::setGold(int gold)
{
    Gold = gold;
}

void Player1::setLives(int lives)
{
    Lives = lives;
}

void Player1::setIncome(int income)
{
    Income = income;
}
