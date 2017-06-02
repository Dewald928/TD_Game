#ifndef CANONTOWER_H
#define CANONTOWER_H

#include <tower.h>
#include <QGraphicsSceneMouseEvent>

class CanonTower: public Tower
{
    Q_OBJECT
public:
    CanonTower(QGraphicsItem * parent =0);
    void fire();
    int getCostOfTower();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void sellTower();
    const int costOfTower = 200;
public slots:
    void aquire_target();

private:
    int towerDamage;

};

#endif // CANONTOWER_H
