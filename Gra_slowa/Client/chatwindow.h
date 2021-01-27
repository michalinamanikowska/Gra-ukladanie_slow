#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
class ChatClient;
class QStandardItemModel;
namespace Ui { class ChatWindow; }
class ChatWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    Ui::ChatWindow *ui;
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;
private slots:
    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    //void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
    void enableGame();
    void startRound(const QString &letters, const int &round);
    void startGame();
    void theEnd(const QString &message);
    void getResult(const QString &resultMessage);
};

#endif // CHATWINDOW_H
