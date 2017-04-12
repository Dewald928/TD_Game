#include "buildcanontowericon.h"
#include <game.h>
#include <canontower.h>

extern Game * game;

BuildCanonTowerIcon::BuildCanonTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/Projectile_Canon.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/2);
}

void BuildCanonTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building) {
        game->building = new CanonTower();
        game->setCursor(QString(":/images/images/Tower_Canon.png"));
    }
}
