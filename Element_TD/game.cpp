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

    //create enemy
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);

    //test code
    BuildArrowTowerIcon * at = new BuildArrowTowerIcon();
    BuildCanonTowerIcon * ct = new BuildCanonTowerIcon();
    BuildFireTowerIcon * ft = new BuildFireTowerIcon();
    ct->setPos(x(),y()+100);
    ft->setPos(x(),y()+200);

    scene->addItem(at);
    scene->addItem(ct);
    scene->addItem(ft);

}

void Game::setCursor(QString filename)
{
    if (cursor) {
        scene->removeItem(cursor);
        //delete cursor; //remove die?
    }
    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor) {
        cursor->setPos(event->pos());
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
        building->setPos(event->pos());
        delete cursor;
        cursor = nullptr;
        building = nullptr;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}
