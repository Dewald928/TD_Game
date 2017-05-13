#include "buildarrowtowericon.h"
#include <game.h>
#include <arrowtower.h>
#include <QDebug>

extern Game * game;

BuildArrowTowerIcon::BuildArrowTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/Projectile_Arrow.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/2);

    //allow hover events
    setAcceptHoverEvents(true);
}

void BuildArrowTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building) {
        game->building = new ArrowTower();
        game->setCursor(QString(":/images/images/Tower_Arrow.png"));
    }
}

void BuildArrowTowerIcon::hoverEnterEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "hovered";
}
