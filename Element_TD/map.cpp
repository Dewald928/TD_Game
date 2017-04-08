#include "map.h"
#include <game.h>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <time.h>
#include <iostream>
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




    //edges

    //portals

    //grass

    //obstructions
}

void Map::printMap()
{

}
