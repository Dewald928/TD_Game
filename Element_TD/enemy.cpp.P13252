#include "enemy.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <map.h>
#include <game.h>

extern Game *game;
extern Map *map;

Enemy::Enemy(QList<QPointF> pointsToFollow, QGraphicsItem *parent)
{
    //set the graphics
    setPixmap(QPixmap(":/images/images/Enemy_Eye.png"));
    int w = pixmap().width();
    int h = pixmap().height();
    setOffset(-w/2,-h/2);

    //set points
    points << pointsToFollow;
    point_index = 0;
    dest = points[0];
    rotateToPoint(dest);

    //connect time to move
    //timer = new QTimer(this);
    connect(game->gametimer, SIGNAL(timeout()), this, SLOT(move_forward()));
    //timer->start(150);

    //enemy default stats
    health = 2500;
    loot = 50;

}

void Enemy::rotateToPoint(QPointF p)
{
    QLineF ln(pos(),p);
    setRotation(-1 * ln.angle());
}

int Enemy::getLoot() const
{
    return loot;
}

void Enemy::setLoot(int value)
{
    loot = value;
}

void Enemy::addDamage(int dam)
{
    health += -dam;
}

void Enemy::move_forward()
{
    //if close to dest, rotate to next dest
    QLineF ln(pos(),dest);
    if ((ln.length() <5))
    {
        point_index++;
        if (point_index >= points.size()){
            return;
        }
        dest = points[point_index];
        rotateToPoint(dest);
    }

    //move enemy at current angle
    STEP_SIZE = 5;
    double theta = rotation(); //degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    game->closestNode(x(),y());
    int y_map = (game->closestNodePos.y() -map->tileY/2)/map->tileY;
    setZValue(y_map);

    //if position at end node deconstruct enemy and take life
    if (y()>= map->mapY*map->tileY - map->tileY) {
        //remove a live
        game->player1->Lives += -1;
        game->updateLives();

        //if all lives are gone
        if (game->player1->Lives <= 0) {
            game->GAMEOVER();
            return;
        }

        deleteLater();
        game->listOfEnemies.removeOne(this);
        //delete this;
        return;
    }
}
