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

extern Game *game;


Tower::Tower(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    //set the graphics
    setPixmap(QPixmap(":/images/images/Tower_Arrow.png"));

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
    QPointF tower_center(x()+pixmap().width()/2,y()+pixmap().height()/2);
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

void Tower::fire()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x()+pixmap().width()/2, y()+pixmap().height()/2);

    QLineF ln(QPointF(x()+pixmap().width()/2, y()+pixmap().height()/2),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
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
            double this_dist = distanceTo(enemy);
            if (this_dist < closest_dist) {
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
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
