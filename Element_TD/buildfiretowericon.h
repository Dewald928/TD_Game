#ifndef BUILDFIRETOWERICON_H
#define BUILDFIRETOWERICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildFireTowerIcon: public QGraphicsPixmapItem
{
public:
    BuildFireTowerIcon(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILDFIRETOWERICON_H
