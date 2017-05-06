#include "mainwindow.h"
#include <QApplication>
#include <game.h>
#include <udpsocket.h>

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
//    w.show();

    game = new Game();
    game->show();
    game->displayMainMenu();

    UDPSocket Host;
    UDPSocket Client;

    Client.sayHello();






    return a.exec();
}
