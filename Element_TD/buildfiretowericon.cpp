#include "buildfiretowericon.h"
#include <game.h>
#include <firetower.h>

extern Game * game;

BuildFireTowerIcon::BuildFireTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/Projectile_Fire.png"));
}

void BuildFireTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building) {
        game->building = new FireTower();
        game->setCursor(QString(":/images/images/Tower_Fire.png"));
        game->building->grabMouse();
    }
}
