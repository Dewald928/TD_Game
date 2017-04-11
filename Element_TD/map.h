#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QList>
#include <node.h>

class Map: public Node
{
public:
    Map();
    int calcH(Node *a, Node *b);
    Node *smallestF();
    void calcNeighbours(Node* n);
    Node *getNode(int x, int y);


    QList <QPointF> nodepoints;

    static const int mapX = 11; //moet ewe getalle wees?
    static const int mapY = 14;
    static const int tileX = 64;
    static const int tileY = 64;
    Node *map[mapX][mapY];
    QPixmap *obstruction, *path, *grass, *portal;
    Node *start;
    Node *finish;
    QList<Node*> openList;
    QList<Node*> closedList;
};

#endif // MAP_H
