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
    QPushButton *pushButton_5;
    QPushButton *sendButton;
    QLabel *label_4;
    QPushButton *pushButton_0;
    QPushButton *pushButton_10;
    QLabel *label_2;
    QPushButton *pushButton_13;
    QPushButton *connectButton;
    QPushButton *pushButton_11;
    QPushButton *pushButton_1;
    QPushButton *pushButton_9;
    QPushButton *pushButton_14;
    QPushButton *pushButton_8;
    QLabel *label_3;
    QListView *chatView;
    QLineEdit *messageEdit;
    QPushButton *pushButton_7;
    QLabel *label;
    QPushButton *pushButton_6;
    QPushButton *startButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_12;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(550, 583);
        gridLayout = new QGridLayout(ChatWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_5 = new QPushButton(ChatWindow);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(100, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("Futura Md BT"));
        font.setPointSize(26);
        font.setBold(false);
        font.setWeight(50);
        pushButton_5->setFont(font);

        gridLayout->addWidget(pushButton_5, 5, 1, 1, 1);

        sendButton = new QPushButton(ChatWindow);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setEnabled(false);

        gridLayout->addWidget(sendButton, 8, 4, 1, 1);

        label_4 = new QLabel(ChatWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Futura Md BT"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 1, 1, 3);

        pushButton_0 = new QPushButton(ChatWindow);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setMinimumSize(QSize(100, 100));
        pushButton_0->setFont(font);

        gridLayout->addWidget(pushButton_0, 5, 0, 1, 1);

        pushButton_10 = new QPushButton(ChatWindow);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(100, 100));
        pushButton_10->setFont(font);

        gridLayout->addWidget(pushButton_10, 6, 4, 1, 1);

        label_2 = new QLabel(ChatWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Futura Md BT"));
        font2.setPointSize(15);
        label_2->setFont(font2);

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        pushButton_13 = new QPushButton(ChatWindow);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setMinimumSize(QSize(100, 100));
        pushButton_13->setFont(font);

        gridLayout->addWidget(pushButton_13, 7, 2, 1, 1);

        connectButton = new QPushButton(ChatWindow);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Futura Bk BT"));
        font3.setPointSize(10);
        connectButton->setFont(font3);

        gridLayout->addWidget(connectButton, 1, 0, 1, 2);

        pushButton_11 = new QPushButton(ChatWindow);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setMinimumSize(QSize(100, 100));
        pushButton_11->setFont(font);

        gridLayout->addWidget(pushButton_11, 7, 0, 1, 1);

        pushButton_1 = new QPushButton(ChatWindow);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setMinimumSize(QSize(100, 100));
        pushButton_1->setFont(font);

        gridLayout->addWidget(pushButton_1, 7, 4, 1, 1);

        pushButton_9 = new QPushButton(ChatWindow);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(100, 100));
        pushButton_9->setFont(font);

        gridLayout->addWidget(pushButton_9, 6, 3, 1, 1);

        pushButton_14 = new QPushButton(ChatWindow);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setMinimumSize(QSize(100, 100));
        pushButton_14->setFont(font);

        gridLayout->addWidget(pushButton_14, 7, 3, 1, 1);

        pushButton_8 = new QPushButton(ChatWindow);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(100, 100));
        pushButton_8->setFont(font);

        gridLayout->addWidget(pushButton_8, 6, 2, 1, 1);

        label_3 = new QLabel(ChatWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Futura Md BT"));
        font4.setPointSize(12);
        label_3->setFont(font4);

        gridLayout->addWidget(label_3, 4, 3, 1, 2);

        chatView = new QListView(ChatWindow);
        chatView->setObjectName(QString::fromUtf8("chatView"));
        chatView->setEnabled(false);
        chatView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(chatView, 3, 0, 1, 5);

        messageEdit = new QLineEdit(ChatWindow);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));
        messageEdit->setEnabled(false);

        gridLayout->addWidget(messageEdit, 8, 0, 1, 4);

        pushButton_7 = new QPushButton(ChatWindow);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(100, 100));
        pushButton_7->setFont(font);

        gridLayout->addWidget(pushButton_7, 6, 1, 1, 1);

        label = new QLabel(ChatWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Futura Bk BT"));
        font5.setPointSize(15);
        label->setFont(font5);

        gridLayout->addWidget(label, 4, 0, 1, 1);

        pushButton_6 = new QPushButton(ChatWindow);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(100, 100));
        pushButton_6->setFont(font);

        gridLayout->addWidget(pushButton_6, 6, 0, 1, 1);

        startButton = new QPushButton(ChatWindow);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        startButton->setFont(font3);

        gridLayout->addWidget(startButton, 1, 3, 1, 2);

        pushButton_4 = new QPushButton(ChatWindow);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(100, 100));
        pushButton_4->setFont(font);

        gridLayout->addWidget(pushButton_4, 5, 2, 1, 1);

        pushButton_3 = new QPushButton(ChatWindow);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 100));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Futura Md BT"));
        font6.setPointSize(26);
        pushButton_3->setFont(font6);

        gridLayout->addWidget(pushButton_3, 5, 3, 1, 1);

        pushButton_12 = new QPushButton(ChatWindow);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setMinimumSize(QSize(100, 100));
        pushButton_12->setFont(font);

        gridLayout->addWidget(pushButton_12, 7, 1, 1, 1);

        pushButton_2 = new QPushButton(ChatWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(100, 100));
        pushButton_2->setFont(font6);

        gridLayout->addWidget(pushButton_2, 5, 4, 1, 1);


        retranslateUi(ChatWindow);

        sendButton->setDefault(true);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Qt Simple Chat Client", nullptr));
        pushButton_5->setText(QString());
        sendButton->setText(QCoreApplication::translate("ChatWindow", "Submit", nullptr));
        label_4->setText(QCoreApplication::translate("ChatWindow", "CREATE WORDS", nullptr));
        pushButton_0->setText(QString());
        pushButton_10->setText(QString());
        label_2->setText(QCoreApplication::translate("ChatWindow", "0", nullptr));
        pushButton_13->setText(QString());
        connectButton->setText(QCoreApplication::translate("ChatWindow", "CONNECT", nullptr));
        pushButton_11->setText(QString());
        pushButton_1->setText(QString());
        pushButton_9->setText(QString());
        pushButton_14->setText(QString());
        pushButton_8->setText(QString());
        label_3->setText(QString());
        pushButton_7->setText(QString());
        label->setText(QCoreApplication::translate("ChatWindow", "POINTS:", nullptr));
        pushButton_6->setText(QString());
        startButton->setText(QCoreApplication::translate("ChatWindow", "START", nullptr));
        pushButton_4->setText(QString());
        pushButton_3->setText(QString());
        pushButton_12->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
