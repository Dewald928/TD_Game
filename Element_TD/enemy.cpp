#include "enemy.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>

Enemy::Enemy(QList<QPointF> pointsToFollow, QGraphicsItem *parent)
{
    //set the graphics
    setPixmap(QPixmap(":/images/images/Enemy_Eye.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/2);

    //set points
    points << pointsToFollow;
    point_index = 0;
    dest = points[0];
    rotateToPoint(dest);

    //connect time to move
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_forward()));
    timer->start(150);

    //enemy default stats
    health = 1000;
    loot = 10;

}

void Enemy::rotateToPoint(QPointF p)
{
    QLineF ln(pos(),p);
    setRotation(-1 * ln.angle());
}

void Enemy::addDamage(int dam)
{
    health += -dam;
}

void Enemy::move_forward()
{
    //if close to dest, rotate to next dest
    QLineF ln(pos(),dest);
    if ((ln.length() <5))
    {
        point_index++;
        if (point_index >= points.size()){
            return;
        }
        dest = points[point_index];
        rotateToPoint(dest);
    }

    //move enemy at current angle
    int STEP_SIZE = 5;
    double theta = rotation(); //degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    //if position at end node deconstruct enemy and take life
}
