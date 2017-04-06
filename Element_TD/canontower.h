#ifndef CANONTOWER_H
#define CANONTOWER_H

#include <tower.h>

class CanonTower: public Tower
{
    Q_OBJECT
public:
    CanonTower(QGraphicsItem * parent =0);
    void fire();
public slots:
    void aquire_target();

};

#endif // CANONTOWER_H
