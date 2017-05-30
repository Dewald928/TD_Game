#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> //list << element baie nice
#include <QPointF>
#include <QTimer>
#include <QGraphicsRectItem>

class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QList<QPointF> pointsToFollow, int enemyNumber, QGraphicsItem * parent=0);
    void rotateToPoint(QPointF p);
    int health;
    int loot;
    void addDamage(int dam);
    int STEP_SIZE;
    QTimer *timer;

    int getLoot() const;
    void setLoot(int value);

public slots:
    void move_forward();

private:
    QList<QPointF> points;
    QPointF dest;
    int point_index;
    QGraphicsRectItem *healthbar;
    int w;
    int h;
    int healthwidth;
    QList<QPixmap> sprites;
    double scale;
    int sprite_counter;
    int enemyCounter;

};

#endif // ENEMY_H
