#include "arrowtower.h"
#include <bullet.h>
#include <QTimer>
#include <game.h>

extern Game *game;


ArrowTower::ArrowTower(QGraphicsItem *parent)
{
    //set the graphics
    setPixmap(QPixmap(":/images/images/Tower_Arrow.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/1.25);

    //setTransformOriginPoint(pixmap().width()/2,pixmap().height()/2);
    //setScale(game->scalingfactor_towers);
    //pixmap().scaled(game->scalingfactor_towers,Qt::KeepAspectRatio);

    //connect timer to aaquire target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(1000);
}

void ArrowTower::fire()
{
    Bullet *bullet = new Bullet();

    //set the graphics
    bullet->setPixmap(QPixmap(":/images/images/Projectile_Arrow.png"));
    bullet->setScale(game->scalingfactor_bullets);

    int y_pos = pixmap().height()*game->scalingfactor_towers/1.25;

    bullet->setPos(x(), y()-y_pos);

    QLineF ln(QPointF(x(), y()-y_pos),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);

}

void ArrowTower::aquire_target()
{
    Tower::aquire_target();
}
