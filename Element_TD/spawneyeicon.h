#ifndef SPAWNEYEICON_H
#define SPAWNEYEICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class SpawnEyeIcon: public QGraphicsPixmapItem
{
public:
    SpawnEyeIcon(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SPAWNEYEICON_H
