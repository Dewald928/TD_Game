#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include <tower.h>
#include <QThread>

class ArrowTower: public Tower
{
    Q_OBJECT
public:
    ArrowTower(QGraphicsItem * parent =0);
    void fire();
    int getCostOfTower();
    const int costOfTower = 100;
public slots:
    void aquire_target();

private:
    QThread workerThread;

};

#endif // ARROWTOWER_H
