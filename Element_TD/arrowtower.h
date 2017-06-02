#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include <tower.h>
#include <QThread>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

class ArrowTower: public Tower
{
    Q_OBJECT
public:
    ArrowTower(QGraphicsItem * parent =0);
    void fire();
    int getCostOfTower();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void sellTower();
    const int costOfTower = 100;
public slots:
    void aquire_target();

private:
    QThread workerThread;
    int towerDamage;

};

#endif // ARROWTOWER_H
