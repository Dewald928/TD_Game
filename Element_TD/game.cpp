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
#include <QLineF>

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
    validplacement = false;
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

        clearPath();
        closestNode(event->pos().x(),event->pos().y());
        snapToGrid();

        //re initialize variables
        delete cursor;
        cursor = nullptr;
        building = nullptr;
        validplacement = false;

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

QPointF Game::closestNode(int x, int y)
{
    QList<QPointF> nodelist = map->nodepoints;
    double distance_old = 10000;
    QPointF closestPoint;

    QListIterator<QPointF> i(nodelist);
    while (i.hasNext()) {
        QPointF nextpoint = i.next();
        QLineF ln(QPointF(x,y),nextpoint);
        double distance_new = ln.length();
        if (distance_new<=distance_old) {
            distance_old = distance_new;
            closestNodePos = nextpoint;

        }
    }
    return closestPoint;
}



void Game::snapToGrid()
{
    //test code
    //map = new Map();
    validplacement = false;

    //clicked node
    int x_map = (closestNodePos.x() -map->tileX/2)/map->tileX;
    int y_map = (closestNodePos.y() -map->tileY/2)/map->tileY;
    clickedNode = new Node();
    clickedNode = map->getNode(x_map,y_map);

    //if it is already a obstruction return
    if (clickedNode->tile == Obstruction) {
        return;
    }
    else
    {
        clickedNode->tile = Obstruction;
        //set map node here
        map->map[x_map][y_map]->tile = Obstruction;
        map->map[x_map][y_map]->cost = 100;

        //run pathfinding
        a_star();
        if (validplacement == true) {
            a_star();
            printmap();

            // otherwise, build at the clicked location
            scene->addItem(building);
            building->setPos(closestNodePos);
            building->setScale(scalingfactor_towers);
        }
        else
        {
            return;

        }
    }
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
    map->openList.clear();
    map->closedList.clear();

    map->closedList.append(map->start);
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
                validplacement = true;
            }

        }
        map->calcNeighbours(t);
    }
}

void Game::clearPath()
{
    for (int i = 0; i < map->mapX; ++i) {
        for (int j = map->mapY -1; j >= 0; --j) {
            map->map[i][j]->x = i;
            map->map[i][j]->y = j;
            map->map[i][j]->f = 0;
            map->map[i][j]->g = 0;
            map->map[i][j]->h = 0;
            map->map[i][j]->parent = 0;
            if (map->map[i][j]->tile == Path) {
                map->map[i][j]->tile = Grass;
            }
            map->map[i][j]->path = false;
        }
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
