#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

class UDPSocket : public QObject
{
    Q_OBJECT
public:
    explicit UDPSocket(QObject *parent = 0);
    void sayHello();
    void send(QString str);
    void processTheDatagram(QNetworkDatagram datagram);
    void emitIP();

    QHostAddress hostAdress;

    QHostAddress getHostAdress() const;
    void setHostAdress(const QHostAddress &value);

signals:

public slots:

private:
    QUdpSocket *socket;

private slots:
    void readPendingDatagrams();

};

#endif // UDPSOCKET_H
