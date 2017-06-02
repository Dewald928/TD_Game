#include "tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <bullet.h>
#include <QLineF>
#include <game.h>
#include <QTimer>
#include <QGraphicsRectItem>
#include <enemy.h>
#include <QPainter>
#include <QLabel>

extern Game *game;


Tower::Tower(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    //set the graphics
    setPixmap(QPixmap(":/images/images/Tower_Arrow.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/1.25);

    //create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3) << QPoint(1,3)
           << QPoint(0,2) << QPoint(0,1);

    //scale points
    int SCALE_FACTOR = pixmap().width();
    for (size_t i=0 , n = points.size() ;i<n ; i++)
    {
        points[i] *= SCALE_FACTOR;
    }

    //create polygon from these points
    QPolygonF polygon(points);

    //create the polyitem
    attack_area = new QGraphicsPolygonItem(polygon,this);
    attack_area->setPen(QPen(Qt::DotLine));

    //move the polygon
    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x(),y());
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    //set attack dest
    attack_dest = QPointF(0,0);
    has_target = false;

}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(), item->pos());
    return ln.length();
}

void Tower::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Tower Clicked";
    if (event->button() == Qt::RightButton) {
        sellTower();
    }
    else
    {
//        QGraphicsView::mousePressEvent(event);
        return;
    }
}

void Tower::fire()
{
    Bullet *bullet = new Bullet();
    int y_pos = pixmap().height()*game->scalingfactor_towers/1.25;

    bullet->setPos(x(), y()-y_pos);

    QLineF ln(QPointF(x(), y()-y_pos),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

int Tower::getCostOfTower()
{
    return costOfTower;
}

void Tower::sellTower()
{
    //sell hier?
    qDebug() << "Sold!";
}

bool Tower::getIsPlaced()
{
    return isPlaced;
}

QString Tower::getOwner()
{
    return owner;
}

void Tower::setIsPlaced(bool b)
{
    isPlaced = b;
}

void Tower::setOwner(QString player)
{
    owner = player;
}

void Tower::aquire_target()
{
    // get a list of all enemies that collide with attack_area, find the closest one
    // and set it's position as the attack_dest

    // get a list of all enemies within attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    // assume tower does not have a target, unless we find one
    has_target = false;

    //find the closest enemy
    double closest_dist = 300;
    QPointF closest_pt(0,0);
    for ( size_t i = 0, n = colliding_items.size(); i <n ; i++)
    {
        //make sure it is an enemy
        Enemy * enemy = dynamic_cast<Enemy *>(colliding_items[i]);

        //see if distance is closer
        if (enemy) {
            double this_dist = distanceTo(colliding_items[i]);
            if (this_dist < closest_dist) {
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();//speel met die pos om center van enemy te kry
                has_target = true;
            }
        }
    }

    //if has target, set the closest enemy as the attack_dest, and fire
    if (has_target == true)
    {
        attack_dest = closest_pt;
        fire();
    }
}
