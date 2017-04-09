#include "map.h"
#include <game.h>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <time.h>
#include <iostream>
#include <node.h>
using namespace std;

extern Game *game;

Map::Map()
{
    //initialize tiles
    grass = new QPixmap(":/images/images/grass.png");
    path = new QPixmap(":/images/images/path.png");
    obstruction = new QPixmap(":/images/images/obstruction.png");
    portal = new QPixmap(":/images/images/portal.png");

    //populate map
    cout << "Start: " << clock() << " "  << endl;
    for (int x  = 0; x < mapX; ++x) {
        for (int y = 0; y < mapY; ++y) {
            Node *t = new Node;
            t->cost = 1;
            t->x = x;
            t->y = y;
            t->f = 0;
            t->g = 0;
            t->h = 0;
            t->parent = 0;
            t->path = false;
            t->tile = Grass;
            map[x][y] = t;

        }
    }

    //EDGES
    /*top row*/
    for (int x  = 0; x < mapX; ++x) {
        for (int y = 0; y < 1; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_007.png"));
        }
    }
    /*bottom row*/
    for (int x  = 0; x < mapX; ++x) {
        for (int y = mapY-1; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_052.png"));
        }
    }

    /*left coloum*/
    for (int x  = 0; x < 1; ++x) {
        for (int y = 0; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_021.png"));
        }
    }

    /*right coloum*/
    for (int x  = mapX-1; x < mapX; ++x) {
        for (int y = 0; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_023.png"));
        }
    }



    //portals
    /*Top portal*/
    for (int x  = mapX/2; x < mapX/2+1; ++x) {
        for (int y = 0; y < 1; ++y) {
            Node *t = new Node;
            t->tile = Grass;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/portal.png"));
        }
    }

    /*Bottom portal*/
    for (int x  = mapX/2; x < mapX/2+1; ++x) {
        for (int y = mapY-1; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Grass;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/portal.png"));
        }
    }

    //obstructions
}


