#include "enemy.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <map.h>
#include <game.h>
#include <QBrush>
#include <QSound>

extern Game *game;
extern Map *map;

Enemy::Enemy(QList<QPointF> pointsToFollow, int enemyNumber, QGraphicsItem *parent)
{
    //create enemy sprites
    enemyCounter = enemyNumber;
    //add if parameter for enemy type
    QPixmap p(":/images/images/sprites.png");
    QPixmap ouBill(":/images/images/OuBill.png");
    sprites.append(ouBill);

    if (enemyNumber == 1) {
        QPixmap eye1 = p.copy(234, 0, 32, 32);
        sprites.append(eye1);
        QPixmap eye2 = p.copy(273, 0, 32, 32);
        sprites.append(eye2);
        scale = 3;
        sprite_counter = enemyNumber;
    }
    else if (enemyNumber == 0) {
        scale = 0.8;
        sprite_counter = 0;
    } else {
        return;
    }




    //set the graphics
    setPixmap(sprites[sprite_counter]);
    setScale(scale);
    w = pixmap().width();
    h = pixmap().height();
    setOffset(-w/2,-h/2);

    //set points
    points << pointsToFollow;
    point_index = 0;
    dest = points[0];
    rotateToPoint(dest);

    //connect time to move
    connect(game->gametimer, SIGNAL(timeout()), this, SLOT(move_forward()));

    //enemy default stats
    health = 2500;
    loot = 50;

    //make health bar
    healthwidth = health/50+game->wave->waveLevel;
    healthbar = new QGraphicsRectItem(this);
    healthbar->setRect(-w/4,-h/1.8, healthwidth/scale,10/scale);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(255,50,20));
    healthbar->setBrush(brush);


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
    //healthwidth = health/50+game->wave->waveLevel;
    healthbar->setRect(-w/4, -h/1.8, (health-dam)/healthwidth/scale, 10/scale);

}

void Enemy::move_forward()
{
    //swap pixmap
    switch (sprite_counter) {
    case 0:
        setPixmap(sprites[0]);
        break;
    case 1:
        setPixmap(sprites[1]);
        sprite_counter++;
        break;
    case 2:
        setPixmap(sprites[2]);
        sprite_counter--;
        break;
    default:
        break;
    }



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

        //play quack
        QSound *quack = new QSound(":/images/sounds/quack.wav");
        quack->play();

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
