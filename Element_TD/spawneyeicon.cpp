#include "spawneyeicon.h"
#include <game.h>

extern Game *game;

SpawnEyeIcon::SpawnEyeIcon(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/Enemy_Eye.png"));
}

void SpawnEyeIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->createEnemies(1);
}
