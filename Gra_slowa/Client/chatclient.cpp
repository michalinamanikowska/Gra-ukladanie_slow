#include <qeventloop.h>
#include <qtimer.h>
#include "chatclient.h"
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
#include <qtimer.h>
#define PORT 2000
ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
    // Reset the m_loggedIn variable when we disconnec. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

void ChatClient::sendToSever(int num, const QString &text)
{
    QString mess = QString::number(num) + "-" + text;
    const char *message;
    QByteArray x = mess.toLatin1();
    message = x.data();
    qDebug() << message;
    send(m_clientSocket->socketDescriptor(), message, 1024, 0);
}

void ChatClient::startGame()
{
    sendToSever(1,"start");
}

void ChatClient::getMessage(const QString &message)
{
    qDebug() << message;
    int type = message.split('-')[0].toInt(), value;
    QString info = message.split('-')[1], text;
    switch(type){
        case 1:
            value = info.split('!')[1].toInt();
            text = info.split('!')[0];
            emit startRound(text, value);
        break;
        case 2:
            emit getResult(info);
        break;
        case 3:
            emit enableGame();
        break;
        case 4:
            emit theEnd(info);
            emit enableGame();
        break;
        case 5:
            emit fullGame(info);
        break;
    }
}


void ChatClient::onReadyRead()
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

void ChatClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // if the client is connected
        sendToSever(0,userName);
    }

    //if (m_clientSocket->state() == QAbstractSocket::ConnectedState) {
        //QDataStream clientStream(m_clientSocket);
        //clientStream.setVersion(QDataStream::Qt_5_7);
        //QJsonObject message;
        //message[QStringLiteral("type")] = QStringLiteral("login");
        //message[QStringLiteral("username")] = userName;
        //clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    //}
}

void ChatClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return; // We don't send empty messages
    // create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);
    // Create the JSON we want to send
    sendToSever(2,text);
    // send the JSON using QDataStream
    //lientStream << QJsonDocument(message).toJson();
    //char mess[20] = "\nhej\n";
    //send(m_clientSocket->socketDescriptor(), mess, sizeof(mess), 0);
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
/*
void ChatClient::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        if (m_loggedIn)
            return; // if we are already logged in we ignore
        // the success field will contain the result of our attempt to login
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return; // the message had no success field so we ignore
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            // we logged in succesfully and we notify it via the loggedIn signal
            emit loggedIn();
            return;
        }
        // the login attempt failed, we extract the reason of the failure from the JSON
        // and notify it via the loginError signal
        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) { //It's a chat message
        // we extract the text field containing the chat text
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        // we extract the sender field containing the username of the sender
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        if (senderVal.isNull() || !senderVal.isString())
            return; // the sender field was invalid so we ignore
        // we notify a new message was received via the messageReceived signal
        emit messageReceived(textVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        emit userJoined(usernameVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat
         // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        emit userLeft(usernameVal.toString());
    }  else if (typeVal.toString().compare(QLatin1String("players"), Qt::CaseInsensitive) == 0) { // A user left the chat
        // we extract the username of the new user
       const QJsonValue numberPlayers = docObj.value(QLatin1String("text"));
       if (numberPlayers.isNull())
           return; // the username was invalid so we ignore
       // we notify of the user disconnection the userLeft signal
       emit letsPlay(numberPlayers.toInt());
   }    else if (typeVal.toString().compare(QLatin1String("letters"), Qt::CaseInsensitive) == 0) { // A user left the chat
        // we extract the username of the new user
       const QJsonValue letters = docObj.value(QLatin1String("text"));
       if (letters.isNull() || !letters.isString())
           return; // the username was invalid so we ignore
       // we notify of the user disconnection the userLeft signal
       emit getLetters(letters.toString());
   }    else if (typeVal.toString().compare(QLatin1String("result"), Qt::CaseInsensitive) == 0) { // A user left the chat
        // we extract the username of the new user
       const QJsonValue resultMessage = docObj.value(QLatin1String("text"));
       const QJsonValue resultValue = docObj.value(QLatin1String("text2"));
       if (resultMessage.isNull() || !resultMessage.isString() || resultValue.isNull())
           return; // the username was invalid so we ignore
       // we notify of the user disconnection the userLeft signal
       emit getResult(resultMessage.toString(),resultValue.toInt());
   }

}*/

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

