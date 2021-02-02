#include "window.h"
#include "ui_window.h"
#include "client.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QHostAddress>
#include <iostream>

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , m_Client(new Client(this))
    , m_Model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    m_Model->insertColumn(0);
    connect(m_Client, &Client::connected, this, &Window::connectedToServer);
    connect(m_Client, &Client::loginError, this, &Window::loginFailed);
    connect(m_Client, &Client::disconnected, this, &Window::disconnectedFromServer);
    connect(m_Client, &Client::error, this, &Window::error);
    connect(m_Client, &Client::fullGame, this, &Window::fullGame);
    connect(m_Client, &Client::theEnd, this, &Window::theEnd);
    connect(m_Client, &Client::enableGame, this, &Window::enableGame);
    connect(m_Client, &Client::startRound, this, &Window::startRound);
    connect(m_Client, &Client::getResult, this, &Window::getResult);
    connect(ui->connectButton, &QPushButton::clicked, this, &Window::attemptConnection);
    connect(ui->startButton, &QPushButton::clicked, this, &Window::startGame);
    connect(ui->sendButton, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &Window::sendMessage);
}

Window::~Window()
{
    delete ui;
}

void Window::startGame()
{
    m_lastUserName.clear();
    m_Client->startGame();
}

void Window::attemptConnection()
{
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty())
        return;

    ui->connectButton->setEnabled(false);
    m_Client->connectToServer(QHostAddress(hostAddress), 2000);
}

void Window::connectedToServer()
{
    bool ok;
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"),
                                                      QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (!ok)
    {
        m_Client->disconnectFromHost();
        return;
    }

    if (newUsername.isEmpty()){
        connectedToServer();
        return;
    }
    else
        attemptLogin(newUsername);
}

void Window::attemptLogin(const QString &userName)
{
    m_Client->login(userName);
}


void Window::loginFailed(const QString &reason)
{
    QMessageBox::critical(this, tr("Error"), reason);
    connectedToServer();
}

void Window::sendMessage()
{
    m_Client->sendMessage(ui->messageEdit->text());

    ui->messageEdit->clear();

}

void Window::disconnectedFromServer()
{
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);

    ui->connectButton->setEnabled(true);
    m_lastUserName.clear();
}


void Window::fullGame()
{
   QMessageBox::warning(this, tr("Cannot join"), tr("Sorry, the game is full"));
   m_Client->disconnectFromHost();
}

void Window::enableGame()
{
    ui->startButton->setEnabled(true);
}

void Window::theEnd(const QString &message)
{
   ui->round->setText("");
   ui->points->setText("");
   ui->result->setText(message);
   if (message.left(11) =="Game won by")
   {
       ui->startButton->setEnabled(true);
       ui->sendButton->setEnabled(false);
       ui->messageEdit->setEnabled(false);
   }
   if (message.left(17) == "Opponents' words:" || message=="None of your opponents have found different words")
   {
       ui->startButton->setEnabled(false);
       ui->sendButton->setEnabled(false);
       ui->messageEdit->setEnabled(false);
       for (int i = 0; i<15; i++) {
          QString objectnameNick = "pushButton_"+QString::number(i);
          QPushButton *nick = findChild<QPushButton *>( objectnameNick );
          if ( nick ) {
             nick->setText("");
          }
      }
   }
}


void Window::startRound(const QString &message)
{
    const QString letters = message.split('!')[0];
    int round = message.split('!')[1].toInt();
    int score = message.split('!')[2].toInt();

    ui->result->setText("Give the word");
    ui->startButton->setEnabled(false);
    ui->sendButton->setEnabled(true);
    ui->messageEdit->setEnabled(true);
    ui->round->setText(QString::number(round));
    ui->points->setText(QString::number(score));

    for (int i = 0; i<15; i++) {
       QString objectnameNick = "pushButton_"+QString::number(i);
       QPushButton *nick = findChild<QPushButton *>( objectnameNick );
       if ( nick ) {
          nick->setText(letters[i]);
       }
   }
}


void Window::getResult(const QString &resultMessage)
{
    QString info = resultMessage;
    int value = info.split('.')[1].toInt();
    info = info.split('.')[0];
    ui->result->setText(info);
    if (info != "10 seconds remaining")
        ui->points->setText(QString::number(value));
}

void Window::error(QAbstractSocket::SocketError socketError)
{
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
    ui->connectButton->setEnabled(true);
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);

    m_lastUserName.clear();
}
