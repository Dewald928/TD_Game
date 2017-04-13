#include "waves.h"
#include <game.h>

extern Game *game;

Waves::Waves()
{
    waveLevel = 1;
    numberOfEnemies = 3;
}

void Waves::nextWave()
{
    game->createEnemies(numberOfEnemies);
    numberOfEnemies += 3;
    waveLevel += 1;
}
