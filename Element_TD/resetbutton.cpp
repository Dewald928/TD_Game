#include "resetbutton.h"
#include <game.h>

extern Game *game;

ResetButton::ResetButton(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/reset.png"));


}

void ResetButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->deleteLater();
    game = new Game();
    game->displayMainMenu();
    game->show();
}
