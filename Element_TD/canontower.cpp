#include "canontower.h"
#include <bullet.h>
#include <QTimer>
#include <game.h>

extern Game *game;


CanonTower::CanonTower(QGraphicsItem *parent)
{
    //set graphics
    setPixmap(QPixmap(":/images/images/Tower_Canon.png"));//nodig?

    //connect timer to aaquire target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(1000);
}

void CanonTower::fire()
{
    //create the bullets
    Bullet *bullet = new Bullet();

    //set the graphics
    bullet->setPixmap(QPixmap(":/images/images/Projectile_Canon.png"));

    bullet->setPos(x()+pixmap().width()/2, y()+pixmap().height()/2);

    QLineF ln(QPointF(x()+pixmap().width()/2, y()+pixmap().height()/2),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);

    game->scene->addItem(bullet);

}

void CanonTower::aquire_target()
{
    Tower::aquire_target();
}
