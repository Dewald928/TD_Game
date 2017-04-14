#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> //list << element baie nice
#include <QPointF>
#include <QTimer>

class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QList<QPointF> pointsToFollow, QGraphicsItem * parent=0);
    void rotateToPoint(QPointF p);
    int health;
    int loot;
    void addDamage(int dam);
    int STEP_SIZE;
    QTimer *timer;

public slots:
    void move_forward();

private:
    QList<QPointF> points;
    QPointF dest;
    int point_index;
};

#endif // ENEMY_H
