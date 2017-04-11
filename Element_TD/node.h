#ifndef NODE_H
#define NODE_H

#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QPointF>

enum TileType
{
    Obstruction =1,
    Path = 2,
    Grass=3,
    Portal = 4
};

class Node: public QGraphicsPixmapItem
{
public:
    Node(QGraphicsItem * parent = 0);
    QLabel *label;
    TileType tile;
    int cost;
    int x;
    int y;
    int f;
    int g;
    int h;
    Node *parent;
    bool path;
    QPointF point;


};

#endif // NODE_H
