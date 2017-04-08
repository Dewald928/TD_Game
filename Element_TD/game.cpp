#include "game.h"
#include <QGraphicsScene>
//#include <tower.h>
#include <arrowtower.h>
#include <canontower.h>
#include <firetower.h>
#include <bullet.h>
#include <enemy.h>
#include <buildarrowtowericon.h>
#include <buildcanontowericon.h>
#include <buildfiretowericon.h>
#include <QTimer>

Game::Game()
{
    //create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1920,1080);

    //set the scene
    setScene(scene);

    //set cursor
    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);

    //alter window
    setMinimumSize(1920,1080);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //create enemy initialize
    spawntimer = new QTimer(this);
    enemiesSpawned = 0;
    maxNumberOfEnemies = 0;
    pointsToFollow <<  QPointF(1000,500);

    createEnemies(5);


    //add building icons
    BuildArrowTowerIcon * at = new BuildArrowTowerIcon();
    BuildCanonTowerIcon * ct = new BuildCanonTowerIcon();
    BuildFireTowerIcon * ft = new BuildFireTowerIcon();
    ct->setPos(x(),y()+100);
    ft->setPos(x(),y()+200);

    at->setScale(scalingfactor_icons);
    ct->setScale(scalingfactor_icons);
    ft->setScale(scalingfactor_icons);

    scene->addItem(at);
    scene->addItem(ct);
    scene->addItem(ft);

}

void Game::setCursor(QString filename)
{
    //creates the building before placing
    if (cursor) {
        scene->removeItem(cursor);
        //delete cursor; //remove die?
    }
    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    cursor->setScale(scalingfactor_towers);
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor) {
        int pos_mouse_x = event->pos().x()- cursor->pixmap().width()*scalingfactor_towers/2;
        int pos_mouse_y = event->pos().y()- cursor->pixmap().height()*scalingfactor_towers/2;
        cursor->setPos(pos_mouse_x,pos_mouse_y);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    //if we are building
    if (building) {
        // return if the cursor is colliding with a tower
        QList<QGraphicsItem *> items = cursor->collidingItems();
        for (size_t i = 0, n = items.size(); i < n; i++){
            if (dynamic_cast<Tower*>(items[i])){
                return;
            }
        }

        // otherwise, build at the clicked location
        scene->addItem(building);
        int pos_mouse_x = event->pos().x()- cursor->pixmap().width()*scalingfactor_towers/2;
        int pos_mouse_y = event->pos().y()- cursor->pixmap().height()*scalingfactor_towers/2;
        building->setPos(pos_mouse_x,pos_mouse_y);
        building->setScale(scalingfactor_towers);

        delete cursor;
        cursor = nullptr;
        building = nullptr;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void Game::createEnemies(int numberOfEnemies)
{
    enemiesSpawned = 0;
    maxNumberOfEnemies = numberOfEnemies;
    connect(spawntimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawntimer->start(1000);
}

void Game::spawnEnemy()
{
    //spawn and enemy
    Enemy *enemy = new Enemy(pointsToFollow);
    enemy->setPos(pointsToFollow[0]);
    scene->addItem(enemy);
    enemiesSpawned += 1;

    if (enemiesSpawned >= maxNumberOfEnemies) {
        spawntimer->disconnect();
    }
}
