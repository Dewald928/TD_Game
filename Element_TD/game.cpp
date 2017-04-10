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
#include <map.h>
#include <node.h>

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

    //create map
    map = new Map();
    a_star();
    printmap();


    //create enemy initialize
    spawntimer = new QTimer(this);
    enemiesSpawned = 0;
    maxNumberOfEnemies = 0;
    pointsToFollow <<  QPointF(0,0);

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

    int w = cursor->pixmap().width();
    int h = cursor->pixmap().height();
    cursor->setOffset(-w/2,-h/1.25);
    cursor->setScale(scalingfactor_towers);

    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor) {
        int pos_mouse_x = event->pos().x();
        int pos_mouse_y = event->pos().y();
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

        //run a star pathfinding when building is placed
        //if there is a valid path, then place building
        a_star();
        printmap();

        // otherwise, build at the clicked location
        scene->addItem(building);
        int pos_mouse_x = event->pos().x();
        int pos_mouse_y = event->pos().y();
        building->setPos(pos_mouse_x,pos_mouse_y);
        building->setScale(scalingfactor_towers);

        //re initialize variables
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

void Game::printmap()
{
    //print map
    for (int i = 0; i < map->mapX; ++i)
    {
        for (int j = map->mapY -1; j >= 0; --j)
        {
            Node *l = new Node();
            switch(map->map[i][j]->tile)
            {
            case Grass://or portal
                if (((i==map->mapX/2)&&(j==0))||((i==map->mapX/2)&&(j==map->mapY-1))) {
                    l->setPixmap(*map->portal);                    
                }
                else
                {
                l->setPixmap(*map->grass);
                }
                break;
            case Path:
                l->setPixmap(*map->path);
                break;
            case Obstruction://or edges
                //if top edge
                if ((i>0)&&(i<map->mapX-1)&&(j==0)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_007.png"));
                }
                //if bottom edge
                else if ((i>0)&&(i<map->mapX-1)&&(j==map->mapY-1)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_052.png"));
                }
                //if left edge
                else if ((i==0)&&(j>0)&&(j<map->mapY-1)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_021.png"));
                }
                //if right edge
                else if ((i==map->mapX-1)&&(j>0)&&(j<map->mapY-1)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_023.png"));
                }
                //if top left corner
                else if ((i==0)&&(j==0))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_006.png"));
                }
                //if top right corner
                else if ((i==map->mapX-1)&&(j==0))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_008.png"));
                }

                //if bottom left corner
                else if ((i==0)&&(j==map->mapY-1))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_051.png"));
                }

                //if bottom right corner
                else if ((i==map->mapX-1)&&(j==map->mapY-1))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_053.png"));
                }
                else
                {
                l->setPixmap(*map->obstruction);
                }
                break;
            }
            int x = i * map->tileX;
            int y = j * map->tileY;
            scene->addItem(l);
            l->setPos(x,y);
            l->setZValue(-1);


        }
    }
}

void Game::a_star()
{
    map->calcNeighbours(map->start);

    while (map->openList.length() > 0)
    {
        Node *t = map->smallestF();
        map->closedList.append(t);
        if (t == map->finish)
        {
            while (t->parent)
            {
                t->path = true;
                t = t->parent;
                t->tile = Path;
                pointsToFollow.prepend(t->point);
            }

        }
        map->calcNeighbours(t);
    }
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
