#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <tower.h>
#include <map.h>
#include <node.h>
#include <player1.h>
#include <QGraphicsTextItem>
#include <QTimer>
#include <enemy.h>


class Game: public QGraphicsView
{
    Q_OBJECT
public:
    //member functions
    Game();
    void displayMainMenu();
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void createEnemies(int numberOfEnemies);

    //snapping to grid
    QPointF closestNode(int x, int y);
    QPointF closestNodePos;
    void snapToGrid();


    //member attributes
    QGraphicsScene *scene;
    QGraphicsPixmapItem * cursor;
    Tower *building;
    QTimer *spawntimer;
    QList<Enemy*> listOfEnemies;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    QList<QPointF> pointsToFollow;
    QGraphicsPixmapItem *statsFrame;

    //map
    Map *map;
    void printmap();
    void a_star();
    void clearPath();
    bool validplacement = false;
    Node *clickedNode;

    //player1
    Player1 *player1;

    //player stats
    QGraphicsTextItem *goldText;
    QGraphicsTextItem *livesText;
    QGraphicsTextItem *timerText;
    QGraphicsTextItem *incomeText;
    QGraphicsPixmapItem *goldIcon;
    QGraphicsPixmapItem *livesIcon;
    QGraphicsPixmapItem *timerIcon;
    QGraphicsPixmapItem *incomeIcon;
    void updateGold();
    void updateLives();
    void updateIncome();

    //waves
    QTimer *waveTimer;
    int timerValue;


    //game constants
    int screenWidth = 1200;
    int screenHeight = 1000;
    int numberOfTowers = 3;
    int numberOfStats = 4;
    const double scalingfactor_towers = 0.3;
    const double scalingfactor_bullets = 0.2;
    const double scalingfactor_icons = 0.5;

public slots:
    void spawnEnemy();
    void startGame();
    void updateTimer();


};

#endif // GAME_H
