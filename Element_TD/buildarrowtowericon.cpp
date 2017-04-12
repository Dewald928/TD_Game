#include "buildarrowtowericon.h"
#include <game.h>
#include <arrowtower.h>

extern Game * game;

BuildArrowTowerIcon::BuildArrowTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/Projectile_Arrow.png"));
}

void BuildArrowTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building) {
        game->building = new ArrowTower();
        game->setCursor(QString(":/images/images/Tower_Arrow.png"));
    }
}
