#include "udpsocket.h"
#include <QDebug>
#include <QNetworkDatagram>
#include <game.h>

extern Game *game;

UDPSocket::UDPSocket(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    socket->bind(700);

    //default
    hostAdress = "127.0.0.1"; //loopback adress
}

void UDPSocket::sayHello()
{
    QByteArray Data;
    Data.append("Hello");
    socket->writeDatagram(Data, hostAdress, 700);
}

void UDPSocket::send(QString str)
{
    QByteArray Data;
    Data.append(str);
    socket->writeDatagram(Data, hostAdress, 700);

    qDebug() << "Sent Datagram";
    qDebug() << Data;
    qDebug() << "700";
    qDebug() << hostAdress;
}

void UDPSocket::processTheDatagram(QNetworkDatagram datagram)
{
    QString sData;
    sData = datagram.data();

    if (sData == "spwn") {
        game->spawnEnemy();
    }

    if (sData == "ACK") {
        hostAdress = QHostAddress(datagram.senderAddress());
        game->connected = true;        
        qDebug() << datagram.senderAddress();
    }

}

void UDPSocket::emitIP()
{

}

QHostAddress UDPSocket::getHostAdress() const
{
    return hostAdress;
}

void UDPSocket::setHostAdress(const QHostAddress &value)
{
    hostAdress = value;
}

void UDPSocket::readPendingDatagrams()
{
    while (socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        processTheDatagram(datagram);
        qDebug() << "Received Datagram";
        qDebug() << datagram.data();
        qDebug() << datagram.senderPort();
        qDebug() << datagram.senderAddress();
    }
}
