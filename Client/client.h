#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
class QHostAddress;
class QJsonDocument;
class Client : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Client)
public:
    explicit Client(QObject *parent = nullptr);
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
    void loginError(const QString &reason);
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void fullGame();
    void theEnd(const QString &message);
    void enableGame();
    void startRound(const QString &message);
    void getResult(const QString &resultMessage);
private:
    QTcpSocket *socket;
    bool logged;
    void jsonReceived(const QJsonObject &doc);
    void getMessage(const QString &message);
    void sendToSever(int num, const QString &text);
};

#endif
