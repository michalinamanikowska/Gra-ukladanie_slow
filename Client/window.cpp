#include "window.h"
#include "ui_window.h"
#include "client.h"
#include <iostream>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QHostAddress>

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , user(new Client(this))
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    model->insertColumn(0);
    connect(user, &Client::connected, this, &Window::connectedToServer);
    connect(user, &Client::loginError, this, &Window::loginFailed);
    connect(user, &Client::disconnected, this, &Window::disconnectedFromServer);
    connect(user, &Client::error, this, &Window::error);
    connect(user, &Client::fullGame, this, &Window::fullGame);
    connect(user, &Client::theEnd, this, &Window::theEnd);
    connect(user, &Client::enableGame, this, &Window::enableGame);
    connect(user, &Client::startRound, this, &Window::startRound);
    connect(user, &Client::getResult, this, &Window::getResult);
    connect(ui->connectButton, &QPushButton::clicked, this, &Window::attemptConnection);
    connect(ui->startButton, &QPushButton::clicked, this, &Window::startGame);
    connect(ui->submitButton, &QPushButton::clicked, this, &Window::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &Window::sendMessage);
}

Window::~Window()
{
    delete ui;
}

void Window::startGame()
{
    last.clear();
    user->startGame();
}

void Window::attemptConnection()
{
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("46.41.143.101")
    );
    if (hostAddress.isEmpty())
        return;

    ui->connectButton->setEnabled(false);
    user->connectToServer(QHostAddress(hostAddress), 2000);
}

void Window::connectedToServer()
{
    bool ok;
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"),
                                                      QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (!ok)
    {
        user->disconnectFromHost();
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
    user->login(userName);
}


void Window::loginFailed(const QString &reason)
{
    QMessageBox::critical(this, tr("Error"), reason);
    connectedToServer();
}

void Window::sendMessage()
{
    user->sendMessage(ui->messageEdit->text());
    ui->messageEdit->clear();

}

void Window::disconnectedFromServer()
{
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    ui->submitButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);

    ui->connectButton->setEnabled(true);
    last.clear();
}

void Window::fullGame()
{
   QMessageBox::warning(this, tr("Cannot join"), tr("Sorry, the game is full"));
   user->disconnectFromHost();
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
       ui->submitButton->setEnabled(false);
       ui->messageEdit->setEnabled(false);
   }
   if (message.left(17) == "Opponents' words:" || message=="None of your opponents have found different words")
   {
       ui->startButton->setEnabled(false);
       ui->submitButton->setEnabled(false);
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
    ui->submitButton->setEnabled(true);
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
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    default:
        Q_UNREACHABLE();
    }
    ui->connectButton->setEnabled(true);
    ui->submitButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);

    last.clear();
}
