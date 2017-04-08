#include "firetower.h"
#include <bullet.h>
#include <QTimer>
#include <game.h>

extern Game *game;


FireTower::FireTower(QGraphicsItem *parent)
{
    //set graphics
    setPixmap(QPixmap(":/images/images/Tower_Fire.png"));//nodig?


    //connect timer to aaquire target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(1000);
}

void FireTower::fire()
{
    //create the bullets
    Bullet *bullet = new Bullet();

    //set the graphics
    bullet->setPixmap(QPixmap(":/images/images/Projectile_Fire.png"));
    bullet->setScale(game->scalingfactor_icons);

    bullet->setPos(x()+pixmap().width()/2, y()+pixmap().height()/2);

    QLineF ln(QPointF(x()+pixmap().width()/2, y()+pixmap().height()/2),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);

    game->scene->addItem(bullet);

}

void FireTower::aquire_target()
{
    Tower::aquire_target();
}
