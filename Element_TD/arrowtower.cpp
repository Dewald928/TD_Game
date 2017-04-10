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
    bullet->setScale(game->scalingfactor_icons);

    //int x_pos = pixmap().width()*game->scalingfactor_bullets/2;
    //int y_pos = pixmap().height()*game->scalingfactor_bullets/2; //dink hieroor
    //int x_pos = pixmap().width()/2;
    //int y_pos = pixmap().height()/2;
    //bullet->setPos(x()+x_pos, y()+y_pos);
    bullet->setPos(x(), y());

    //QLineF ln(QPointF(x()+pixmap().width()/2, y()+pixmap().height()/2),attack_dest);
    QLineF ln(QPointF(x(), y()),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);

}

void ArrowTower::aquire_target()
{
    Tower::aquire_target();
}
