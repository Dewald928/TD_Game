#include "game.h"
#include <QGraphicsScene>
#include <arrowtower.h>
#include <canontower.h>
#include <firetower.h>
#include <bullet.h>
#include <enemy.h>
#include <buildarrowtowericon.h>
#include <buildcanontowericon.h>
#include <buildfiretowericon.h>
#include <QTimer>
#include <map.h>
#include <node.h>
#include <QLineF>
#include <spawneyeicon.h>
#include <button.h>
#include <QGraphicsTextItem>

Game::Game()
{
    //create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,screenWidth,screenHeight);
    scene->setBackgroundBrush(QColor(213,173,81));

    //set the scene
    setScene(scene);

    //alter window
    setMinimumSize(screenWidth,screenHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set cursor
    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);

    //create map
    map = new Map();

}

void Game::displayMainMenu()
{
    //create brackground
    QGraphicsPixmapItem *backgroundImage = new QGraphicsPixmapItem;
    backgroundImage->setPixmap(QString(":/images/images/test.png"));
    backgroundImage->setScale(1);
    backgroundImage->setPos(-375,-200);
    scene->addItem(backgroundImage);

    //create the title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Element Tower Defense"));
    QFont titleFont("Pixel Emulator", 40);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(QColor("white"));
    int txpos = this->width()/2 - titleText->boundingRect().width()/2;
    int typos = 200;
    titleText->setPos(txpos,typos);
    scene->addItem(titleText);

    //create play button
    Button *playbutton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playbutton->boundingRect().width()/2;
    int byPos = 500;
    playbutton->setPos(bxPos,byPos);
    connect(playbutton,SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playbutton);

    //create quit button
    Button *quitbutton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitbutton->boundingRect().width()/2;
    int qyPos = 600;
    quitbutton->setPos(qxPos,qyPos);
    connect(quitbutton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitbutton);

}

void Game::setCursor(QString filename)
{
    //creates the building before placing
    if (cursor) {
        scene->removeItem(cursor);
        //delete cursor; //remove die?
    }
    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));

    int w = cursor->pixmap().width();
    int h = cursor->pixmap().height();
    cursor->setOffset(-w/2,-h/1.25);
    cursor->setScale(scalingfactor_towers);

    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor) {
        int pos_mouse_x = event->pos().x();
        int pos_mouse_y = event->pos().y();
        cursor->setPos(pos_mouse_x,pos_mouse_y);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    //if we are building
    if (building) {

        clearPath();
        closestNode(event->pos().x(),event->pos().y());
        snapToGrid();

        //re initialize variables
        delete cursor;
        cursor = nullptr;
        building = nullptr;
        validplacement = false;

    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void Game::createEnemies(int numberOfEnemies)
{
    enemiesSpawned = 0;
    maxNumberOfEnemies = numberOfEnemies;
    connect(spawntimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawntimer->start(1000);
}

QPointF Game::closestNode(int x, int y)
{
    QList<QPointF> nodelist = map->nodepoints;
    double distance_old = 10000;
    QPointF closestPoint;

    QListIterator<QPointF> i(nodelist);
    while (i.hasNext()) {
        QPointF nextpoint = i.next();
        QLineF ln(QPointF(x,y),nextpoint);
        double distance_new = ln.length();
        if (distance_new<=distance_old) {
            distance_old = distance_new;
            closestNodePos = nextpoint;

        }
    }
    return closestPoint;
}



void Game::snapToGrid()
{
    //test code
    //map = new Map();
    validplacement = false;

    //clicked node
    int x_map = (closestNodePos.x() -map->tileX/2)/map->tileX;
    int y_map = (closestNodePos.y() -map->tileY/2)/map->tileY;
    clickedNode = new Node();
    clickedNode = map->getNode(x_map,y_map);


    //if it is already a obstruction return
    if (clickedNode->tile == Obstruction) {
        return;
    }
    else
    {

        player1->Gold += -building->getCostOfTower();
        //if enough gold place tower
        if (player1->getGold() >= 0) {
            // otherwise, build at the clicked location
            updateGold();


            clickedNode->tile = Obstruction;
            //set map node here
            map->map[x_map][y_map]->tile = Obstruction;
            map->map[x_map][y_map]->cost = 100;

            //run pathfinding
            a_star();
            if (validplacement == true) {
                a_star();
                printmap();
                scene->addItem(building);
                building->setPos(closestNodePos);
                building->setScale(scalingfactor_towers);
            }
            else
            {
                clickedNode->tile = Grass;
                //set map node here
                map->map[x_map][y_map]->tile = Grass;
                map->map[x_map][y_map]->cost = 1;
                return;

            }
        }
        else
        {
            player1->Gold += building->costOfTower;
            return;
        }
    }

}



void Game::printmap()
{
    //print map
    for (int i = 0; i < map->mapX; ++i)
    {
        for (int j = map->mapY -1; j >= 0; --j)
        {
            Node *l = new Node();
            switch(map->map[i][j]->tile)
            {
            case Grass://or portal
                if (((i==map->mapX/2)&&(j==0))||((i==map->mapX/2)&&(j==map->mapY-1))) {
                    l->setPixmap(*map->portal);
                }
                else
                {
                    l->setPixmap(*map->grass);
                }
                break;
            case Path:
                l->setPixmap(*map->path);
                break;
            case Obstruction://or edges
                //if top edge
                if ((i>0)&&(i<map->mapX-1)&&(j==0)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_007.png"));
                }
                //if bottom edge
                else if ((i>0)&&(i<map->mapX-1)&&(j==map->mapY-1)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_052.png"));
                }
                //if left edge
                else if ((i==0)&&(j>0)&&(j<map->mapY-1)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_021.png"));
                }
                //if right edge
                else if ((i==map->mapX-1)&&(j>0)&&(j<map->mapY-1)) {
                    l->setPixmap(QPixmap(":/images/images/mapTile_023.png"));
                }
                //if top left corner
                else if ((i==0)&&(j==0))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_006.png"));
                }
                //if top right corner
                else if ((i==map->mapX-1)&&(j==0))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_008.png"));
                }

                //if bottom left corner
                else if ((i==0)&&(j==map->mapY-1))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_051.png"));
                }

                //if bottom right corner
                else if ((i==map->mapX-1)&&(j==map->mapY-1))
                {
                    l->setPixmap(QPixmap(":/images/images/mapTile_053.png"));
                }
                else
                {
                    l->setPixmap(*map->obstruction);
                }
                break;
            }
            int x = i * map->tileX;
            int y = j * map->tileY;
            scene->addItem(l);
            l->setPos(x,y);
            l->setZValue(-1);


        }
    }
}

void Game::a_star()
{
    map->openList.clear();
    map->closedList.clear();

    map->closedList.append(map->start);
    map->calcNeighbours(map->start);

    while (map->openList.length() > 0)
    {
        Node *t = map->smallestF();
        map->closedList.append(t);
        if (t == map->finish)
        {
            while (t->parent)
            {
                t->path = true;
                t = t->parent;
                t->tile = Path;
                pointsToFollow.prepend(t->point);
                validplacement = true;
            }

        }
        map->calcNeighbours(t);
    }
}

void Game::clearPath()
{
    for (int i = 0; i < map->mapX; ++i) {
        for (int j = map->mapY -1; j >= 0; --j) {
            map->map[i][j]->x = i;
            map->map[i][j]->y = j;
            map->map[i][j]->f = 0;
            map->map[i][j]->g = 0;
            map->map[i][j]->h = 0;
            map->map[i][j]->parent = 0;
            if (map->map[i][j]->tile == Path) {
                map->map[i][j]->tile = Grass;
            }
            map->map[i][j]->path = false;
        }
    }
}

void Game::updateGold()
{
    //update gold
    goldText->deleteLater();
    goldText = new QGraphicsTextItem(QString::number(player1->getGold()));
    QFont goldFont("Pixel Emulator", 14);
    goldText->setFont(goldFont);
    goldText->setDefaultTextColor(QColor("white"));
    int xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    int ygoldPos = statsFrame->pixmap().height()*0.7/(numberOfStats+1)*1 +10;
    int txgpos = xgoldPos + goldIcon->pixmap().width()/3*0.55 + 5;
    int tygpos = ygoldPos +10;
    goldText->setPos(txgpos,tygpos);
    scene->addItem(goldText);
}

void Game::updateLives()
{
    //update lives
    livesText->deleteLater();
    livesText = new QGraphicsTextItem(QString::number(player1->getLives()));
    QFont livesFont("Pixel Emulator", 14);
    livesText->setFont(livesFont);
    livesText->setDefaultTextColor(QColor("white"));
    int xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    int ygoldPos = statsFrame->pixmap().height()*0.7/(numberOfStats+1)*2 +10;
    int txlpos = xgoldPos + livesIcon->pixmap().width()/3*0.55 + 5;
    int tylpos = ygoldPos +10;
    livesText->setPos(txlpos,tylpos);
    scene->addItem(livesText);
}

void Game::updateIncome()
{
    //update income
    incomeText->deleteLater();
    incomeText = new QGraphicsTextItem(QString::number(player1->getIncome()));
    QFont incomeFont("Pixel Emulator", 14);
    incomeText->setFont(incomeFont);
    incomeText->setDefaultTextColor(QColor("white"));
    double incomeScale = 0.42;
    int xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    int ygoldPos = statsFrame->pixmap().height()*0.7/(numberOfStats+1)*4 +10;
    int txipos = xgoldPos + incomeIcon->pixmap().width()*0.7*incomeScale + 5;
    int tyipos = ygoldPos +10;
    incomeText->setPos(txipos,tyipos);
    scene->addItem(incomeText);
}


void Game::spawnEnemy()
{
    //spawn and enemy
    Enemy *enemy = new Enemy(pointsToFollow);
    listOfEnemies << enemy;
    enemy->setPos(pointsToFollow[0]);
    scene->addItem(enemy);
    enemiesSpawned += 1;

    if (enemiesSpawned >= maxNumberOfEnemies) {
        spawntimer->disconnect();
    }
}

void Game::startGame()
{
    //clear the screen
    scene->clear();

    /*create game instance*/
    //set cursor
    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);

    //create map
    map = new Map();
    validplacement = false;
    a_star();
    printmap();

    //initialize player1
    player1 = new Player1;


    //create enemy initialize
    spawntimer = new QTimer(this);
    enemiesSpawned = 0;
    maxNumberOfEnemies = 0;

    //add stats bar
    statsFrame = new QGraphicsPixmapItem();
    statsFrame->setPixmap(QString(":/images/images/frame3.png"));
    double framescale = 0.7;
    statsFrame->setScale(framescale);
    statsFrame->setPos(map->mapX*map->tileX+15,50);
    statsFrame->setZValue(-1);
    scene->addItem(statsFrame);

    /*add stats*/
    //gold frame
    goldIcon = new QGraphicsPixmapItem();
    goldIcon->setPixmap(QString(":/images/images/gold.png"));
    int xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    int ygoldPos = statsFrame->pixmap().height()*framescale/(numberOfStats+1) +10;
    double goldscale = 0.45;
    goldIcon->setPos(xgoldPos,ygoldPos);
    goldIcon->setScale(goldscale);
    goldIcon->setZValue(0);
    scene->addItem(goldIcon);
    //add text info
    goldText = new QGraphicsTextItem(QString::number(player1->getGold()));
    QFont goldFont("Pixel Emulator", 14);
    goldText->setFont(goldFont);
    goldText->setDefaultTextColor(QColor("white"));
    int txgpos = xgoldPos + goldIcon->pixmap().width()/3*goldscale + 5;
    int tygpos = ygoldPos +10;
    goldText->setPos(txgpos,tygpos);
    scene->addItem(goldText);


    //lives
    livesIcon = new QGraphicsPixmapItem();
    livesIcon->setPixmap(QString(":/images/images/lives.png"));
    xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    ygoldPos = statsFrame->pixmap().height()*framescale/(numberOfStats+1)*2 +10;
    livesIcon->setPos(xgoldPos,ygoldPos);
    livesIcon->setScale(0.46);
    livesIcon->setZValue(0);
    scene->addItem(livesIcon);
    //add lives info
    livesText = new QGraphicsTextItem(QString::number(player1->getLives()));
    QFont livesFont("Pixel Emulator", 14);
    livesText->setFont(livesFont);
    livesText->setDefaultTextColor(QColor("white"));
    int txlpos = xgoldPos + livesIcon->pixmap().width()/3*0.55 + 5;
    int tylpos = ygoldPos +10;
    livesText->setPos(txlpos,tylpos);
    scene->addItem(livesText);

    //start timer
    waveTimer = new QTimer(this);
    connect(waveTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    waveTimer->start(1000);

    //wave timers
    timerIcon = new QGraphicsPixmapItem();
    timerIcon->setPixmap(QString(":/images/images/timer.png"));
    xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    ygoldPos = statsFrame->pixmap().height()*framescale/(numberOfStats+1)*3 +10;
    timerIcon->setPos(xgoldPos,ygoldPos);
    timerIcon->setScale(0.45);
    timerIcon->setZValue(0);
    scene->addItem(timerIcon);
    //add timer info
    timerValue = 60;
    timerText = new QGraphicsTextItem(QString::number(timerValue));
    QFont timerFont("Pixel Emulator", 14);
    timerText->setFont(timerFont);
    timerText->setDefaultTextColor(QColor("white"));
    int txtpos = xgoldPos + timerIcon->pixmap().width()*0.6*0.55 + 5;
    int tytpos = ygoldPos +10;
    timerText->setPos(txtpos,tytpos);
    scene->addItem(timerText);

    //income
    incomeIcon = new QGraphicsPixmapItem();
    incomeIcon->setPixmap(QString(":/images/images/income.png"));
    xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    ygoldPos = statsFrame->pixmap().height()*framescale/(numberOfStats+1)*4 +10;
    incomeIcon->setPos(xgoldPos,ygoldPos);
    double incomeScale = 0.42;
    incomeIcon->setScale(incomeScale);
    incomeIcon->setZValue(0);
    scene->addItem(incomeIcon);
    //add income info
    incomeText = new QGraphicsTextItem(QString::number(player1->getIncome()));
    QFont incomeFont("Pixel Emulator", 14);
    incomeText->setFont(incomeFont);
    incomeText->setDefaultTextColor(QColor("white"));
    int txipos = xgoldPos + incomeIcon->pixmap().width()*0.7*incomeScale + 5;
    int tyipos = ygoldPos +10;
    incomeText->setPos(txipos,tyipos);
    scene->addItem(incomeText);



    ///*add building frame*/
    QGraphicsPixmapItem *buildingsFrame = new QGraphicsPixmapItem();
    buildingsFrame->setPixmap(QString(":/images/images/buildings.png"));
    int ybfrPos = statsFrame->pixmap().height()*framescale;
    buildingsFrame->setPos(map->mapX*map->tileX + map->tileX/2 , ybfrPos +50);
    buildingsFrame->setScale(0.7);
    buildingsFrame->setZValue(-1);
    scene->addItem(buildingsFrame);


    //add building icons
    BuildArrowTowerIcon * at = new BuildArrowTowerIcon();
    BuildCanonTowerIcon * ct = new BuildCanonTowerIcon();
    BuildFireTowerIcon * ft = new BuildFireTowerIcon();
    int xIconPos = map->mapX*map->tileX + statsFrame->pixmap().width()/2*framescale + 15;
    int yIconPos = (screenHeight -150 - statsFrame->pixmap().height()*framescale)/numberOfTowers;
    int offset = statsFrame->pixmap().height()*framescale;

    at->setPos(xIconPos,yIconPos + offset);
    ct->setPos(xIconPos,(yIconPos*2 + offset)*0.9);
    ft->setPos(xIconPos,(yIconPos*3 + offset)*0.9);

    at->setScale(scalingfactor_icons);
    ct->setScale(scalingfactor_icons);
    ft->setScale(scalingfactor_icons);

    scene->addItem(at);
    scene->addItem(ct);
    scene->addItem(ft);

    //add evenmy icons
    SpawnEyeIcon *eyeIcon = new SpawnEyeIcon;
    eyeIcon->setPos(x(),y()+map->mapY*map->tileY);
    scene->addItem(eyeIcon);


}

void Game::updateTimer()
{
    timerValue -= 1;

    timerText->deleteLater();
    timerText = new QGraphicsTextItem(QString::number(timerValue));
    QFont timerFont("Pixel Emulator", 14);
    timerText->setFont(timerFont);
    timerText->setDefaultTextColor(QColor("white"));
    int xgoldPos = map->mapX*map->tileX + map->tileX+ 15;
    int ygoldPos = statsFrame->pixmap().height()*0.7/(numberOfStats+1)*3 +10;
    int txtpos = xgoldPos + timerIcon->pixmap().width()*0.6*0.55 + 5;
    int tytpos = ygoldPos +10;
    timerText->setPos(txtpos,tytpos);
    scene->addItem(timerText);

    if (timerValue <= 0) {
        timerValue = 60;
        //emit soos 'n signal hier?
    }
}
