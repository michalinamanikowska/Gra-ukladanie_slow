/****************************************************************************
** Meta object code from reading C++ file 'chatwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Gra_slowa/Client/chatwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatWindow_t {
    QByteArrayData data[28];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatWindow_t qt_meta_stringdata_ChatWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatWindow"
QT_MOC_LITERAL(1, 11, 17), // "attemptConnection"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "connectedToServer"
QT_MOC_LITERAL(4, 48, 12), // "attemptLogin"
QT_MOC_LITERAL(5, 61, 8), // "userName"
QT_MOC_LITERAL(6, 70, 11), // "loginFailed"
QT_MOC_LITERAL(7, 82, 6), // "reason"
QT_MOC_LITERAL(8, 89, 15), // "messageReceived"
QT_MOC_LITERAL(9, 105, 4), // "text"
QT_MOC_LITERAL(10, 110, 11), // "sendMessage"
QT_MOC_LITERAL(11, 122, 22), // "disconnectedFromServer"
QT_MOC_LITERAL(12, 145, 10), // "userJoined"
QT_MOC_LITERAL(13, 156, 8), // "username"
QT_MOC_LITERAL(14, 165, 8), // "userLeft"
QT_MOC_LITERAL(15, 174, 5), // "error"
QT_MOC_LITERAL(16, 180, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(17, 209, 11), // "socketError"
QT_MOC_LITERAL(18, 221, 10), // "enableGame"
QT_MOC_LITERAL(19, 232, 8), // "fullGame"
QT_MOC_LITERAL(20, 241, 7), // "message"
QT_MOC_LITERAL(21, 249, 10), // "startRound"
QT_MOC_LITERAL(22, 260, 7), // "letters"
QT_MOC_LITERAL(23, 268, 5), // "round"
QT_MOC_LITERAL(24, 274, 9), // "startGame"
QT_MOC_LITERAL(25, 284, 6), // "theEnd"
QT_MOC_LITERAL(26, 291, 9), // "getResult"
QT_MOC_LITERAL(27, 301, 13) // "resultMessage"

    },
    "ChatWindow\0attemptConnection\0\0"
    "connectedToServer\0attemptLogin\0userName\0"
    "loginFailed\0reason\0messageReceived\0"
    "text\0sendMessage\0disconnectedFromServer\0"
    "userJoined\0username\0userLeft\0error\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "enableGame\0fullGame\0message\0startRound\0"
    "letters\0round\0startGame\0theEnd\0getResult\0"
    "resultMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    1,   96,    2, 0x08 /* Private */,
       6,    1,   99,    2, 0x08 /* Private */,
       8,    1,  102,    2, 0x08 /* Private */,
      10,    0,  105,    2, 0x08 /* Private */,
      11,    0,  106,    2, 0x08 /* Private */,
      12,    1,  107,    2, 0x08 /* Private */,
      14,    1,  110,    2, 0x08 /* Private */,
      15,    1,  113,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    1,  117,    2, 0x08 /* Private */,
      21,    2,  120,    2, 0x08 /* Private */,
      24,    0,  125,    2, 0x08 /* Private */,
      25,    1,  126,    2, 0x08 /* Private */,
      26,    1,  129,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   22,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   27,

       0        // eod
};

void ChatWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChatWindow *_t = static_cast<ChatWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attemptConnection(); break;
        case 1: _t->connectedToServer(); break;
        case 2: _t->attemptLogin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sendMessage(); break;
        case 6: _t->disconnectedFromServer(); break;
        case 7: _t->userJoined((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->userLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 10: _t->enableGame(); break;
        case 11: _t->fullGame((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->startRound((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 13: _t->startGame(); break;
        case 14: _t->theEnd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->getResult((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject ChatWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChatWindow.data,
      qt_meta_data_ChatWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ChatWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
