#include <qeventloop.h>
#include <qtimer.h>
#include "client.h"
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <qeventloop.h>

#define PORT 2000
Client::Client(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    connect(m_clientSocket, &QTcpSocket::connected, this, &Client::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

void Client::sendToSever(int num, const QString &text)
{
    QString mess = QString::number(num) + "-" + text;
    const char *message;
    QByteArray x = mess.toLatin1();
    message = x.data();
    send(m_clientSocket->socketDescriptor(), message, 1024, 0);
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
    QByteArray jsonData;
    QDataStream socketStream(m_clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_7);

    QString data;
    while(m_clientSocket->bytesAvailable())
    {
        data = m_clientSocket->readAll();
        getMessage(data);
        QEventLoop loop;
        QTimer::singleShot(100, &loop, SLOT(quit()));
        loop.exec();
    }
}

void Client::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState)
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
    m_clientSocket->disconnectFromHost();
}

void Client::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

