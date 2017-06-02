#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QMouseEvent>

class Tower:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower(QGraphicsItem *parent = 0);
    double distanceTo(QGraphicsItem * item);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void fire();
    virtual int getCostOfTower();
    virtual void sellTower();
    const int costOfTower = 50;


    //getters
    bool getIsPlaced();
    QString getOwner();

    //setters
    void setIsPlaced(bool b);
    void setOwner(QString player);


public slots:
    void aquire_target();

protected:
    //placements
    bool isPlaced = false;
    QString owner;


    //attacking
    QGraphicsPolygonItem *attack_area;
    bool has_target;
    QPointF attack_dest;
};

#endif // TOWER_H
