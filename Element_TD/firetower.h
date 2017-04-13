#ifndef FIRETOWER_H
#define FIRETOWER_H

#include <tower.h>

class FireTower: public Tower
{
    Q_OBJECT
public:
    FireTower(QGraphicsItem * parent =0);
    void fire();
    const int costOfTower = 300;
public slots:
    void aquire_target();

};

#endif // FIRETOWER_H
