#ifndef NODE_H
#define NODE_H

#include <QLabel>

enum TileType
{
    Obstruction =1,
    Path = 2,
    Grass=3
};

class Node
{
public:
    Node();
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
};

#endif // NODE_H
