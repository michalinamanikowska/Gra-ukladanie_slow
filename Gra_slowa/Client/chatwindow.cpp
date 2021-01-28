#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "chatclient.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <iostream>
ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow) // create the elements defined in the .ui file
    , m_chatClient(new ChatClient(this)) // create the chat client
    , m_chatModel(new QStandardItemModel(this)) // create the model to hold the messages
{
    // set up of the .ui file
    ui->setupUi(this);
    // the model for the messages will have 1 column
    m_chatModel->insertColumn(0);
    // set the model as the data source vor the list view
    //ui->chatView->setModel(m_chatModel);
    // connect the signals from the chat client to the slots in this ui
    connect(m_chatClient, &ChatClient::connected, this, &ChatWindow::connectedToServer);
    //connect(m_chatClient, &ChatClient::loggedIn, this, &ChatWindow::loggedIn);
    connect(m_chatClient, &ChatClient::loginError, this, &ChatWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &ChatWindow::messageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &ChatWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &ChatWindow::error);
    connect(m_chatClient, &ChatClient::userJoined, this, &ChatWindow::userJoined);
    connect(m_chatClient, &ChatClient::userLeft, this, &ChatWindow::userLeft);
    connect(m_chatClient, &ChatClient::fullGame, this, &ChatWindow::fullGame);
    connect(m_chatClient, &ChatClient::theEnd, this, &ChatWindow::theEnd);
    connect(m_chatClient, &ChatClient::enableGame, this, &ChatWindow::enableGame);
    connect(m_chatClient, &ChatClient::startRound, this, &ChatWindow::startRound);
    connect(m_chatClient, &ChatClient::getResult, this, &ChatWindow::getResult);
    // connect the connect button to a slot that will attempt the connection
    connect(ui->connectButton, &QPushButton::clicked, this, &ChatWindow::attemptConnection);
    connect(ui->startButton, &QPushButton::clicked, this, &ChatWindow::startGame);
    // connect the click of the "send" button and the press of the enter while typing to the slot that sends the message
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(ui->messageEdit, &QLineEdit::returnPressed, this, &ChatWindow::sendMessage);
}

ChatWindow::~ChatWindow()
{
    // delete the elements created from the .ui file
    delete ui;
}

void ChatWindow::startGame()
{
    // clear the user name record
    m_lastUserName.clear();
    m_chatClient->startGame();
}

void ChatWindow::attemptConnection()
{
    // We ask the user for the address of the server, we use 127.0.0.1 (aka localhost) as default
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty())
        return; // the user pressed cancel or typed nothing
    // disable the connect button to prevent the user clicking it again
    ui->connectButton->setEnabled(false);
    // tell the client to connect to the host using the port 2000
    m_chatClient->connectToServer(QHostAddress(hostAddress), 2000);
}

void ChatWindow::connectedToServer()
{
    // once we connected to the server we ask the user for what username they would like to use
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        // if the user clicked cancel or typed nothing, we just disconnect from the server
        return m_chatClient->disconnectFromHost();
    }
    // try to login with the given username
    attemptLogin(newUsername);
}

void ChatWindow::attemptLogin(const QString &userName)
{
    // use the client to attempt a log in with the given username
    m_chatClient->login(userName);
}
/*
void ChatWindow::loggedIn()
{
    // once we successully log in we enable the ui to display and send messages
    ui->sendButton->setEnabled(true);
    ui->messageEdit->setEnabled(true);
    // clear the user name record
    m_lastUserName.clear();
}*/

void ChatWindow::loginFailed(const QString &reason)
{
    // the server rejected the login attempt
    // display the reason for the rejection in a message box
    QMessageBox::critical(this, tr("Error"), reason);
    // allow the user to retry, execute the same slot as when just connected
    connectedToServer();
}

void ChatWindow::messageReceived(const QString &text)
{
    int newRow = m_chatModel->rowCount();
    m_chatModel->insertRow(newRow);
    m_chatModel->setData(m_chatModel->index(newRow, 0), text);
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    //ui->chatView->scrollToBottom();
}

void ChatWindow::sendMessage()
{
    // we use the client to send the message that the user typed
    m_chatClient->sendMessage(ui->messageEdit->text());

    // now we add the message to the list
    // store the index of the new row to append to the model containing the messages
    //const int newRow = m_chatModel->rowCount();
    // insert a row for the message
    //m_chatModel->insertRow(newRow);
    // store the message in the model
    //m_chatModel->setData(m_chatModel->index(newRow, 0), ui->messageEdit->text());
    // set the alignment for the message
    //m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // clear the content of the message editor
    ui->messageEdit->clear();
    // scroll the view to display the new message
    //ui->chatView->scrollToBottom();
    // reset the last printed username
    //m_lastUserName.clear();
}

void ChatWindow::disconnectedFromServer()
{
    // if the client loses connection to the server
    // comunicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    // disable the ui to send and display messages
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);
    //ui->chatView->setEnabled(false);
    // enable the button to connect to the server again
    ui->connectButton->setEnabled(true);
    // reset the last printed username
    m_lastUserName.clear();
}

void ChatWindow::userJoined(const QString &username)
{
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user joined
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Joined the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);
    // scroll the view to display the new message
    //ui->chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}
void ChatWindow::userLeft(const QString &username)
{
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to comunicate a user left
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Left the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    // scroll the view to display the new message
    //ui->chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}


void ChatWindow::fullGame(const QString &message)
{
   ui->result->setText(message);
}

void ChatWindow::enableGame()
{
    ui->startButton->setEnabled(true);
}

void ChatWindow::theEnd(const QString &message)
{
   ui->round->setText("");
   ui->points->setText("");
   ui->result->setText(message);
   if (message.left(11) =="Game won by")
       ui->startButton->setEnabled(true);
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


void ChatWindow::startRound(const QString &message)
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


void ChatWindow::getResult(const QString &resultMessage)
{
    QString info = resultMessage;
    int value = info.split('.')[1].toInt();
    info = info.split('.')[0];
    ui->result->setText(info);
    if (info != "10 seconds remaining")
        ui->points->setText(QString::number(value));
}

void ChatWindow::error(QAbstractSocket::SocketError socketError)
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
    // enable the button to connect to the server again
    ui->connectButton->setEnabled(true);
    // disable the ui to send and display messages
    ui->sendButton->setEnabled(false);
    ui->messageEdit->setEnabled(false);
    //ui->chatView->setEnabled(false);
    // reset the last printed username
    m_lastUserName.clear();
}
