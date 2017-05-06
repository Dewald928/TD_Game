#include "spawneyeicon.h"
#include <game.h>
#include <enemy.h>

extern Game *game;

SpawnEyeIcon::SpawnEyeIcon(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/images/Enemy_Eye.png"));
}

void SpawnEyeIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //game->createEnemies(1);
    game->player1->Gold += -50;  //enemy loot value //test code

    if (game->player1->Gold >= 0) {
        game->Client->send("spwn");
        game->player1->Income += 5;
        game->updateIncome();
        game->updateGold();
    }
    else
    {
        game->player1->Gold += 50;
        return;
    }


}
