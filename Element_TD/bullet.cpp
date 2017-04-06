#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>


Bullet::Bullet(QGraphicsItem *parent)
{
    //set graphics
    setPixmap(QPixmap(":/images/images/Projectile_Arrow.png"));

    //connect timer to move
    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(50);
}

void Bullet::move()
{
    int STEP_SIZE = 30;
    double theta = rotation(); //degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);


}
