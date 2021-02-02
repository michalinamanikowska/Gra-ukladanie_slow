#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QAbstractSocket>
class Client;
class QStandardItemModel;
namespace Ui { class Window; }
class Window : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(Window)
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
private:
    Ui::Window *ui;
    Client *user;
    QStandardItemModel *model;
    QString last;
private slots:
    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loginFailed(const QString &reason);
    void sendMessage();
    void disconnectedFromServer();
    void error(QAbstractSocket::SocketError socketError);
    void fullGame();
    void startRound(const QString &message);
    void startGame();
    void theEnd(const QString &message);
    void enableGame();
    void getResult(const QString &resultMessage);
};

#endif
