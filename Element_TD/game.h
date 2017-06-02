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
#include <waves.h>
#include <udpsocket.h>
#include <QSound>



class Game: public QGraphicsView
{
    Q_OBJECT
public:
    //member functions
    Game();
    ~Game();
    void displayMainMenu();
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void createEnemies(int numberOfEnemies);
    void GAMEOVER();
    void Victory();
    bool GameOver = false;
    QTimer *gametimer;
    QTimer *bulletTimer;

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
    QList<Tower*> listOfTowers;
    int enemiesSpawned;
    int maxNumberOfEnemies;
    int enemyHealthIncrease = 0;
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
    QGraphicsTextItem *waveText;
    QGraphicsPixmapItem *goldIcon;
    QGraphicsPixmapItem *livesIcon;
    QGraphicsPixmapItem *timerIcon;
    QGraphicsPixmapItem *incomeIcon;
    QGraphicsPixmapItem *waveIcon;
    void updateGold();
    void updateLives();
    void updateIncome();
    void updateWave();

    //waves
    Waves *wave;
    QTimer *waveTimer;
    int timerValue;

    //networking parameters
    //UDPSocket *Host;
    UDPSocket *Client;
    bool connected = false;
    QTimer *conTimer;


    //game constants
    int screenWidth = 1200;
    int screenHeight = 1000;
    int numberOfTowers = 3;
    int numberOfStats = 5; //gold, lives, times, income, level
    const double scalingfactor_towers = 0.28;
    const double scalingfactor_bullets = 0.2;
    const double scalingfactor_icons = 0.5;

public slots:
    void spawnEnemy(int enemyNum);
    void spawnEnemy();
    void startGame();
    void updateTimer();
    void waitConnection();
    void connectionEstablished();
    void join();

};

#endif // GAME_H
