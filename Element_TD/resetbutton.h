#ifndef RESETBUTTON_H
#define RESETBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ResetButton: public QGraphicsPixmapItem
{
public:
    ResetButton(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RESETBUTTON_H
