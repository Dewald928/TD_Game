#include "firetower.h"
#include <bullet.h>
#include <QTimer>
#include <game.h>

extern Game *game;


FireTower::FireTower(QGraphicsItem *parent)
{
    //set graphics
    setPixmap(QPixmap(":/images/images/Tower_Fire.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/1.25);


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
    bullet->setPixmap(QPixmap(":/images/images/Projectile_Fire-min.png"));
    //bullet->setScale(game->scalingfactor_bullets);

    //set the damage
    bullet->damage = 40;

    int y_pos = pixmap().height()*game->scalingfactor_towers/1.25; //make it shoot from top of tower

    bullet->setPos(x(), y()-y_pos);

    QLineF ln(QPointF(x(), y()-y_pos),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);

    game->scene->addItem(bullet);

}

int FireTower::getCostOfTower()
{
    return costOfTower;
}

void FireTower::aquire_target()
{
    Tower::aquire_target();
}


void FireTower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

   qDebug() << "Clicked Tower";

   //right mouse sell
    if (event->button() == Qt::RightButton) {
        sellTower();
    }
    else
    {
        //        QGraphicsView::mousePressEvent(event);
        return;
    }

}

void FireTower::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //upgrade tower
    setPixmap(QPixmap(":/images/images/Tower_Fire_2.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/1.25);

    //upgrade damage
    towerDamage = 70;

    //update gold
    game->player1->Gold += -costOfTower/2;
    game->updateGold();

}

void FireTower::sellTower()
{
    qDebug() << "sold arrow";
    //meh
}
