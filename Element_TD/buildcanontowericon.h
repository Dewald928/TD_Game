#ifndef BUILDCANONTOWERICON_H
#define BUILDCANONTOWERICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildCanonTowerIcon: public QGraphicsPixmapItem
{
public:
    BuildCanonTowerIcon(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILDCANONTOWERICON_H
