#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include <tower.h>

class ArrowTower: public Tower
{
    Q_OBJECT
public:
    ArrowTower(QGraphicsItem * parent =0);
    void fire();
public slots:
    void aquire_target();

};

#endif // ARROWTOWER_H
