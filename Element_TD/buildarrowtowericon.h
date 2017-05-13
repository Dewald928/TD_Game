#ifndef BUILDARROWTOWERICON_H
#define BUILDARROWTOWERICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildArrowTowerIcon: public QGraphicsPixmapItem
{
public:
    BuildArrowTowerIcon(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILDARROWTOWERICON_H
