#include "buildtowericon.h"
#include <game.h>

extern Game * game;

BuildTowerIcon::BuildTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/Projectile_Arrow.png"));
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->build) {
        game->build = new Tower();
        game->setCursor(QString(":/images/images/Tower_Arrow.png"));
    }
}
