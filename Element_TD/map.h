#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QList>
#include <node.h>
#include <game.h>

class Map: public Node
{
public:
    Map();
    int calcH(Node *a, Node *b);
    Node* smallestF();
    void calcNeighbours(Node* n);
    void printMap();


private:
    static const int mapX = 20;
    static const int mapY = 20;
    static const int tileX = 64;
    static const int tileY = 32;
    Node *map[mapX][mapY];
    QPixmap *obstruction, *path, *grass, *portal;
    Node *start;
    Node *finish;
    QList<Node*> openList;
    QList<Node*> closedList;
};

#endif // MAP_H
