#include "chatserver.h"
#include "serverworker.h"
#include <QThread>
#include <functional>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>
#include <QString>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QVector>
#include <QString>
#include <QFile>
#include <QApplication>
ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Connected"));
}
void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}
void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->userName().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
    if (!userName.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
        disconnectedMessage[QStringLiteral("username")] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + QLatin1String(" disconnected"));
    }
    sender->deleteLater();
}

void ChatServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
}

void ChatServer::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void ChatServer::letsPlay()
{
    QJsonObject players;
    players[QStringLiteral("type")] = QStringLiteral("players");
    players[QStringLiteral("text")] = m_clients.size();
    broadcast(players, nullptr);
}

void ChatServer::sendLetters()
{
    srand(time(NULL));
    int ascii;
    QString letters;
    for (int i=0;i<15;i++)
    {
        ascii = 97 + rand()%26;
        letters = letters + (char)ascii;
    }

    QJsonObject set;
    set[QStringLiteral("type")] = QStringLiteral("letters");
    set[QStringLiteral("text")] = letters;
    broadcast(set, nullptr);
    LettersInGame = letters;
}

void ChatServer::get_dictionary()
{
    QFile file("D:/OneDrive/Dokumenty/semestr 5/SK/Gra-ukladanie_slow/Gra_slowa/Server/dictionary.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString slowo = file.readLine();
            slowo.resize(slowo.size() - 1);
            dictionary.push_back(slowo);
        }
    }
    else
        std::cout<<"Blad danych";
    file.close();
}

bool ChatServer::check_dictionary(QString slowo)
{
    for (int i=0;i<dictionary.size();i++)
    {
        if (dictionary[i]==slowo)
            return true;
    }
    return false;
}

bool ChatServer::check_word(QString slowo)
{
    int check;
    QString lista = LettersInGame;
    for (int i=0;i<slowo.size();i++)
    {
        check = 0;
        for (int j=0;j<lista.size();j++)
            if (slowo[i]==lista[j])
                {
                    lista.remove(j,1);
                    check = 1;
                    break;
                }
        if (check == 0)
            return false;
    }
    return true;
}

bool ChatServer::check_base(QString slowo)
{
    for (int i=0;i<base.size();i++)
        if (base[i]==slowo)
            return false;
    base.push_back(slowo);
    return true;
}

void ChatServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (ServerWorker *worker : qAsConst(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("success")] = false;
            message[QStringLiteral("reason")] = QStringLiteral("duplicate username");
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);
    QJsonObject successMessage;
    successMessage[QStringLiteral("type")] = QStringLiteral("login");
    successMessage[QStringLiteral("success")] = true;
    sendJson(sender, successMessage);
    letsPlay();
    QJsonObject connectedMessage;
    connectedMessage[QStringLiteral("type")] = QStringLiteral("newuser");
    connectedMessage[QStringLiteral("username")] = newUserName;
    broadcast(connectedMessage, sender);
}

void ChatServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    QString wynik;
    int punkty;
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0){
        const QJsonValue answer = docObj.value(QLatin1String("text"));
        if (answer.isNull() || !answer.isString())
            return;
        punkty = 0;
        get_dictionary();
        if (answer.toString().length()<3)
            wynik = "This word is too short";
        else if (!check_word(answer.toString()))
            wynik = "This word cannot be made from the given letters";
        else if (!check_dictionary(answer.toString()))
            wynik = "Such a word does not exist";
        else if (!check_base(answer.toString()))
            wynik = "This word has already been given";
        else if (answer.toString()!="")
           {
           wynik = "You entered the correct word, congratulations!";
           punkty = answer.toString().length();
           }
        QJsonObject result;
        result[QStringLiteral("type")] = QStringLiteral("result");
        result[QStringLiteral("text")] = wynik;
        result[QStringLiteral("text2")] = punkty;
        sendJson(sender, result);
    }
    if (typeVal.toString().compare(QLatin1String("start"), Qt::CaseInsensitive) == 0)
        sendLetters();
}


