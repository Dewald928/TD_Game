#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <enemy.h>
#include <QDebug>
#include <typeinfo>
#include <game.h>

extern Game *game;


Bullet::Bullet(QGraphicsItem *parent)
{
    //set graphics
    setPixmap(QPixmap(":/images/images/Projectile_Arrow.png"));


    //connect timer to move
    //QTimer * move_timer = new QTimer(this);
    connect(game->bulletTimer, SIGNAL(timeout()),this,SLOT(move()));
    //move_timer->start(50);

    //initialize values
    maxRange =250;
    distanceTravelled = 0;
    damage = 1;
}

int Bullet::getDamage()
{
    return damage;
}

void Bullet::move()
{
    int STEP_SIZE = 30;
    double theta = rotation(); //degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    distanceTravelled += STEP_SIZE;

    //if collides with enemy
    QList<QGraphicsItem*> colliding_items = collidingItems();
        for(int i=0, n=colliding_items.size(); i<n; i++){
            if(typeid(*(colliding_items[i]))==typeid(Enemy))
            {
             Enemy* asEnemy = dynamic_cast<Enemy*>(colliding_items[i]);
             asEnemy->addDamage(damage); // CREATE addDamage function in Enemy

             if (asEnemy->health <= 0) {
             //scene()->removeItem(asEnemy);
             game->player1->Gold += asEnemy->loot;
             game->updateGold();
             qDebug() << "You be dead son!";
             deleteLater();
             //delete this;
             //delete asEnemy;
             asEnemy->deleteLater();
             game->listOfEnemies.removeOne(asEnemy);
             return;
           }
//             deleteLater();
//             delete this;
        }
        }


    //if over max range
    if (distanceTravelled >= maxRange) {
        deleteLater();
        //delete this;
    }


}

double Bullet::getMaxRange(){
    return maxRange;
}

double Bullet::getDistanceTravelled(){
    return distanceTravelled;
}

void Bullet::setMaxRange(double rng){
    maxRange = rng;
}

void Bullet::setDistanceTravelled(double dist){
    distanceTravelled = dist;
}
