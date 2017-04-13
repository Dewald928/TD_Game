#include "canontower.h"
#include <bullet.h>
#include <QTimer>
#include <game.h>

extern Game *game;


CanonTower::CanonTower(QGraphicsItem *parent)
{
    //set graphics
    setPixmap(QPixmap(":/images/images/Tower_Canon.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/1.25);

    //connect timer to aaquire target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(2000);
}

void CanonTower::fire()
{
    //create the bullets
    Bullet *bullet = new Bullet();

    //set the graphics
    bullet->setPixmap(QPixmap(":/images/images/Projectile_Canon.png"));
    bullet->setScale(game->scalingfactor_bullets);

    //set the damage
    bullet->damage = 30;

    int y_pos = pixmap().height()*game->scalingfactor_towers/1.25;

    bullet->setPos(x(), y()-y_pos);

    QLineF ln(QPointF(x(), y()-y_pos),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);

    game->scene->addItem(bullet);

}

int CanonTower::getCostOfTower()
{
    return costOfTower;
}

void CanonTower::aquire_target()
{
    Tower::aquire_target();
}
