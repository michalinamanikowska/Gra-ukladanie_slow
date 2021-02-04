#include <qeventloop.h>
#include <qtimer.h>
#include "client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <qeventloop.h>

#define PORT 2000

Client::Client(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
    , logged(false)
{
    connect(socket, &QTcpSocket::connected, this, &Client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);
    connect(socket, &QTcpSocket::disconnected, this, [this]()->void{logged = false;});
}

void Client::sendToSever(int num, const QString &text)
{
    QString mess = QString::number(num) + "-" + text;
    const char *message;
    QByteArray x = mess.toLatin1();
    message = x.data();
    send(socket->socketDescriptor(), message, 1024, 0);
}

void Client::startGame()
{
    sendToSever(1,"start");
}

void Client::getMessage(const QString &message)
{
    int type = message.split('-')[0].toInt();
    QString info = message.split('-')[1];
    switch(type){
        case 1:
            emit startRound(info);
        break;
        case 2:
            emit getResult(info);
        break;
        case 3:
            emit enableGame();
        break;
        case 4:
            emit theEnd(info);
        break;
        case 5:
            emit fullGame();
        break;
    }
}

void Client::onReadyRead()
{
    QString message;
    while(socket->bytesAvailable())
    {
        message = socket->readAll();
        getMessage(message);
    }
}

void Client::login(const QString &userName)
{
    if (socket->state() == QAbstractSocket::ConnectedState)
        sendToSever(0,userName);
}

void Client::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return;

    sendToSever(2,text);

}

void Client::disconnectFromHost()
{
    socket->disconnectFromHost();
}

void Client::connectToServer(const QHostAddress &address, quint16 port)
{
    socket->connectToHost(address, port);
}

