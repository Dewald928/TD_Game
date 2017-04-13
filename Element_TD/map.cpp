#include "map.h"
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <time.h>
//#include <iostream>
#include <node.h>
//using namespace std;
#include "game.h"

extern Game *game;

Map::Map()
{
    //initialize tiles
    grass = new QPixmap(":/images/images/grass.png");
    path = new QPixmap(":/images/images/path.png");
    obstruction = new QPixmap(":/images/images/obstruction.png");
    portal = new QPixmap(":/images/images/portal.png");

    //populate map
    //cout << "Start: " << clock() << " "  << endl;
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
            int x_pos = x*pixmap().width() + pixmap().width()/2;
            int y_pos = y*pixmap().height() + pixmap().height()/2;
            t->point = QPointF(x_pos,y_pos);
            map[x][y] = t;
            map[x][y]->setPos(x,y);
            nodepoints << QPointF(x_pos, y_pos);

        }
    }

    //EDGES //add die cost
    /*top row*/
    for (int x  = 0; x < mapX; ++x) {
        for (int y = 0; y < 1; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            t->cost = 100;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_007.png"));
        }
    }
    /*bottom row*/
    for (int x  = 0; x < mapX; ++x) {
        for (int y = mapY-1; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            t->cost = 100;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_052.png"));
        }
    }

    /*left coloum*/
    for (int x  = 0; x < 1; ++x) {
        for (int y = 0; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            t->cost = 100;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_021.png"));
        }
    }

    /*right coloum*/
    for (int x  = mapX-1; x < mapX; ++x) {
        for (int y = 0; y < mapY; ++y) {
            Node *t = new Node;
            t->tile = Obstruction;
            t->cost = 100;
            map[x][y] = t;
            t->setPixmap(QPixmap(":/images/images/mapTile_023.png"));
        }
    }



    //portals
    /*Top portal*/
    for (int x  = mapX/2; x < mapX/2+1; ++x) {
        for (int y = 0; y < 1; ++y) {
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
            t->setPixmap(QPixmap(":/images/images/portal.png"));
        }
    }

    /*Bottom portal*/
    for (int x  = mapX/2; x < mapX/2+1; ++x) {
        for (int y = mapY-1; y < mapY; ++y) {
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
            t->setPixmap(QPixmap(":/images/images/portal.png"));
        }
    }

//    //test code (set random node)
//    map[10][7]->cost = 100;
//    map[10][7]->tile = Obstruction;

    //set beginning and en points
    start = map[mapX/2][0];
    finish = map[mapX/2][mapY-1];
    start->point = QPointF(mapX*tileX/2, tileY/2);
    finish->point = QPointF(mapX*tileX/2, mapY*tileY - tileY/2);

    //sets start node to closed list and calculate neighbors
    closedList.append(start);
    calcNeighbours(start);

    //start A*
    //cout << "InitMap" << clock() << endl;

//    while (openList.length() > 0)
//    {
//        Node *t = smallestF();
//        closedList.append(t);
//        if (t == finish)
//        {
//            while (t->parent)
//            {
//                t->path = true;
//                t = t->parent;
//                t->tile = Path;
//                game->pointsToFollow << point;
//            }

//        }
//        calcNeighbours(t);
//    }

    //cout << "Path found: " << clock() << endl;

    //cout << " Map printed: " << clock() << endl;


}

int Map::calcH(Node *a, Node *b)
{
    int x, y;
    a->x - b->x >= 0 ? x = a->x - b->x : x = b->x; //weti of kla
    a->y - b->y >= 0 ? y = a->y - b->y : y = b->y; //weti of kla
    return x >= y ? x * 10 : y * 10;
}

Node *Map::smallestF()
{
    Node *r = openList.first();
    QListIterator<Node*> i(openList);
    while (i.hasNext())
    {
        Node *t = i.next();
        if (t->f < r->f)
            r = t;
    }
    openList.removeOne(r);
    return r;
}

void Map::calcNeighbours(Node *n)
{
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            int x = dx + n->x;
            int y = dy + n->y;
            if ((x>=0) && (x < mapX) && (y>=0) && (y < mapY) &&
                (!openList.contains(map[x][y])) && (!closedList.contains(map[x][y])) &&
                (map[x][y]->cost < 100) && ((dx*dx) || (dy*dy))) //nie die actual node nie.
            {
                map[x][y]->parent = n;
                if ((dx*dx) && (dy*dy))
                {
                    map[x][y]->g = n->g + 14;
                }
                else
                {
                    map[x][y]->g = n->g + 10;
                }
                map[x][y]->h = calcH(map[x][y], finish);
                map[x][y]->f = map[x][y]->g + map[x][y]->h;
                openList.append(map[x][y]);
            }
        }
    }
}

Node *Map::getNode(int x, int y)
{
    return map[x][y];
}




