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

    //move the polygon
    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+pixmap().width()/2,y()+pixmap().height()/2);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    //connect timer to attacktarget
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(attack_target()));
    timer->start(1000);

    //set attack dest
    attack_dest = QPointF(800,0);



}

void Tower::attack_target()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x()+pixmap().width()/2, y()+pixmap().height()/2);

    QLineF ln(QPointF(x()+pixmap().width()/2, y()+pixmap().height()/2),attack_dest);
    int angle = -1*ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);



}
