#include "node.h"
#include <game.h>

extern Game *game;



Node::Node(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/grass.png"));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //if node is not an obstruction
    game->nodeClicked(this);

}

//void Node::mouseTest(QGraphicsSceneMouseEvent *event)
//{
//    //if node is not an obstruction
//    game->nodeClicked(this);
//}
