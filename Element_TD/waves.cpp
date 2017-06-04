#include "waves.h"
#include <game.h>
#include <enemy.h>

extern Game *game;

Waves::Waves()
{
    waveLevel = 1;
    numberOfEnemies = 1;
}

void Waves::nextWave()
{
    game->createEnemies(numberOfEnemies);
    game->enemyHealthIncrease += 300;
    numberOfEnemies += 1;
    waveLevel += 1;

}
