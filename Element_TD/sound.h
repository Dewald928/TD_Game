#ifndef SOUND_H
#define SOUND_H


#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QSound>

class Sound: public QGraphicsPixmapItem
{
public:
    Sound(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool playing;
    QSound *theme;
};

#endif // SOUND_H
