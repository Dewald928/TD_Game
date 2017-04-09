#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <tower.h>
#include <map.h>


class Game: public QGraphicsView
{
    Q_OBJECT
public:
    //member functions
    Game();
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void createEnemies(int numberOfEnemies);

    //member attributes
    QGraphicsScene *scene;
    QGraphicsPixmapItem * cursor;
    Tower *building;
    QTimer *spawntimer;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    QList<QPointF> pointsToFollow;

    //map
    Map *map;
    void printmap();


    //game constants
    const double scalingfactor_towers = 0.5;
    const double scalingfactor_bullets = 0.5;
    const double scalingfactor_icons = 0.5;

public slots:
    void spawnEnemy();



};

#endif // GAME_H
