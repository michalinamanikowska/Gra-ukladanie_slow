/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_0;
    QPushButton *pushButton_1;
    QLabel *label;
    QPushButton *pushButton_3;
    QPushButton *pushButton_13;
    QPushButton *startButton;
    QPushButton *pushButton_9;
    QPushButton *sendButton;
    QPushButton *pushButton_14;
    QPushButton *pushButton_10;
    QListView *chatView;
    QPushButton *pushButton_12;
    QPushButton *connectButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_11;
    QPushButton *pushButton_2;
    QPushButton *pushButton_6;
    QLabel *title;
    QLineEdit *messageEdit;
    QPushButton *pushButton_7;
    QPushButton *pushButton_5;
    QLabel *points;
    QPushButton *pushButton_8;
    QLabel *result;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(550, 620);
        gridLayout = new QGridLayout(ChatWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_0 = new QPushButton(ChatWindow);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setMinimumSize(QSize(100, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("Futura Md BT"));
        font.setPointSize(26);
        font.setBold(false);
        font.setWeight(50);
        pushButton_0->setFont(font);

        gridLayout->addWidget(pushButton_0, 9, 0, 1, 1);

        pushButton_1 = new QPushButton(ChatWindow);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setMinimumSize(QSize(100, 100));
        pushButton_1->setFont(font);

        gridLayout->addWidget(pushButton_1, 11, 4, 1, 1);

        label = new QLabel(ChatWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Futura Bk BT"));
        font1.setPointSize(15);
        label->setFont(font1);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        pushButton_3 = new QPushButton(ChatWindow);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 100));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Futura Md BT"));
        font2.setPointSize(26);
        pushButton_3->setFont(font2);

        gridLayout->addWidget(pushButton_3, 9, 3, 1, 1);

        pushButton_13 = new QPushButton(ChatWindow);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setMinimumSize(QSize(100, 100));
        pushButton_13->setFont(font);

        gridLayout->addWidget(pushButton_13, 11, 2, 1, 1);

        startButton = new QPushButton(ChatWindow);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Futura Bk BT"));
        font3.setPointSize(10);
        startButton->setFont(font3);

        gridLayout->addWidget(startButton, 1, 3, 1, 2);

        pushButton_9 = new QPushButton(ChatWindow);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(100, 100));
        pushButton_9->setFont(font);

        gridLayout->addWidget(pushButton_9, 10, 3, 1, 1);

        sendButton = new QPushButton(ChatWindow);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setEnabled(false);

        gridLayout->addWidget(sendButton, 12, 4, 1, 1);

        pushButton_14 = new QPushButton(ChatWindow);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setMinimumSize(QSize(100, 100));
        pushButton_14->setFont(font);

        gridLayout->addWidget(pushButton_14, 11, 3, 1, 1);

        pushButton_10 = new QPushButton(ChatWindow);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(100, 100));
        pushButton_10->setFont(font);

        gridLayout->addWidget(pushButton_10, 10, 4, 1, 1);

        chatView = new QListView(ChatWindow);
        chatView->setObjectName(QString::fromUtf8("chatView"));
        chatView->setEnabled(false);
        chatView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(chatView, 2, 0, 1, 5);

        pushButton_12 = new QPushButton(ChatWindow);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setMinimumSize(QSize(100, 100));
        pushButton_12->setFont(font);

        gridLayout->addWidget(pushButton_12, 11, 1, 1, 1);

        connectButton = new QPushButton(ChatWindow);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setFont(font3);

        gridLayout->addWidget(connectButton, 1, 0, 1, 2);

        pushButton_4 = new QPushButton(ChatWindow);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(100, 100));
        pushButton_4->setFont(font);

        gridLayout->addWidget(pushButton_4, 9, 2, 1, 1);

        pushButton_11 = new QPushButton(ChatWindow);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setMinimumSize(QSize(100, 100));
        pushButton_11->setFont(font);

        gridLayout->addWidget(pushButton_11, 11, 0, 1, 1);

        pushButton_2 = new QPushButton(ChatWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 100));
        pushButton_2->setFont(font2);

        gridLayout->addWidget(pushButton_2, 9, 4, 1, 1);

        pushButton_6 = new QPushButton(ChatWindow);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(100, 100));
        pushButton_6->setFont(font);

        gridLayout->addWidget(pushButton_6, 10, 0, 1, 1);

        title = new QLabel(ChatWindow);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Futura Md BT"));
        font4.setPointSize(18);
        font4.setBold(true);
        font4.setWeight(75);
        title->setFont(font4);
        title->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(title, 0, 1, 1, 3);

        messageEdit = new QLineEdit(ChatWindow);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));
        messageEdit->setEnabled(false);

        gridLayout->addWidget(messageEdit, 12, 0, 1, 4);

        pushButton_7 = new QPushButton(ChatWindow);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(100, 100));
        pushButton_7->setFont(font);

        gridLayout->addWidget(pushButton_7, 10, 1, 1, 1);

        pushButton_5 = new QPushButton(ChatWindow);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(100, 100));
        pushButton_5->setFont(font);

        gridLayout->addWidget(pushButton_5, 9, 1, 1, 1);

        points = new QLabel(ChatWindow);
        points->setObjectName(QString::fromUtf8("points"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Futura Md BT"));
        font5.setPointSize(15);
        points->setFont(font5);

        gridLayout->addWidget(points, 5, 1, 1, 1);

        pushButton_8 = new QPushButton(ChatWindow);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(100, 100));
        pushButton_8->setFont(font);

        gridLayout->addWidget(pushButton_8, 10, 2, 1, 1);

        result = new QLabel(ChatWindow);
        result->setObjectName(QString::fromUtf8("result"));
        result->setMinimumSize(QSize(0, 0));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Futura Bk BT"));
        font6.setPointSize(14);
        result->setFont(font6);

        gridLayout->addWidget(result, 6, 0, 1, 5);


        retranslateUi(ChatWindow);

        sendButton->setDefault(true);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Qt Simple Chat Client", nullptr));
        pushButton_0->setText(QString());
        pushButton_1->setText(QString());
        label->setText(QCoreApplication::translate("ChatWindow", "POINTS:", nullptr));
        pushButton_3->setText(QString());
        pushButton_13->setText(QString());
        startButton->setText(QCoreApplication::translate("ChatWindow", "START", nullptr));
        pushButton_9->setText(QString());
        sendButton->setText(QCoreApplication::translate("ChatWindow", "Submit", nullptr));
        pushButton_14->setText(QString());
        pushButton_10->setText(QString());
        pushButton_12->setText(QString());
        connectButton->setText(QCoreApplication::translate("ChatWindow", "CONNECT", nullptr));
        pushButton_4->setText(QString());
        pushButton_11->setText(QString());
        pushButton_2->setText(QString());
        pushButton_6->setText(QString());
        title->setText(QCoreApplication::translate("ChatWindow", "CREATE WORDS", nullptr));
        pushButton_7->setText(QString());
        pushButton_5->setText(QString());
        points->setText(QCoreApplication::translate("ChatWindow", "0", nullptr));
        pushButton_8->setText(QString());
        result->setText(QCoreApplication::translate("ChatWindow", "Give the word", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
