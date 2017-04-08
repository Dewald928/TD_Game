#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Tower:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower(QGraphicsItem *parent = 0);
    double distanceTo(QGraphicsItem * item);
    virtual void fire();


public slots:
    void aquire_target();

protected:
    QGraphicsPolygonItem *attack_area;
    bool has_target;
    QPointF attack_dest;
};

#endif // TOWER_H
