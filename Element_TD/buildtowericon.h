#ifndef BUILDTOWERICON_H
#define BUILDTOWERICON_H
//delete die header en source later
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildTowerIcon: public QGraphicsPixmapItem
{
public:
    BuildTowerIcon(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILDTOWERICON_H
