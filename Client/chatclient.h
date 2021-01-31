#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
class QHostAddress;
class QJsonDocument;
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void disconnectFromHost();
    void startGame();
private slots:
    void onReadyRead();
signals:
    void connected();
    //void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void fullGame(const QString &message);
    void theEnd(const QString &message);
    void enableGame();
    void startRound(const QString &message);
    void getResult(const QString &resultMessage);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
    void getMessage(const QString &message);
    void sendToSever(int num, const QString &text);
};

#endif // CHATCLIENT_H
