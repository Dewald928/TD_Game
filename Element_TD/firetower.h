#ifndef FIRETOWER_H
#define FIRETOWER_H

#include <tower.h>
#include <QGraphicsSceneMouseEvent>

class FireTower: public Tower
{
    Q_OBJECT
public:
    FireTower(QGraphicsItem * parent =0);
    void fire();
    int getCostOfTower();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void sellTower();
    const int costOfTower = 300;
public slots:
    void aquire_target();
private:
    int towerDamage;

};

#endif // FIRETOWER_H
