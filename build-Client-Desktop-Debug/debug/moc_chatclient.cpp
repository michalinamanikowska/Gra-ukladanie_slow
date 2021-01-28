/****************************************************************************
** Meta object code from reading C++ file 'chatclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Gra_slowa/Client/chatclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatClient_t {
    QByteArrayData data[33];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatClient_t qt_meta_stringdata_ChatClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatClient"
QT_MOC_LITERAL(1, 11, 9), // "connected"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "loginError"
QT_MOC_LITERAL(4, 33, 6), // "reason"
QT_MOC_LITERAL(5, 40, 12), // "disconnected"
QT_MOC_LITERAL(6, 53, 15), // "messageReceived"
QT_MOC_LITERAL(7, 69, 4), // "text"
QT_MOC_LITERAL(8, 74, 5), // "error"
QT_MOC_LITERAL(9, 80, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(10, 109, 11), // "socketError"
QT_MOC_LITERAL(11, 121, 10), // "userJoined"
QT_MOC_LITERAL(12, 132, 8), // "username"
QT_MOC_LITERAL(13, 141, 8), // "userLeft"
QT_MOC_LITERAL(14, 150, 10), // "enableGame"
QT_MOC_LITERAL(15, 161, 8), // "fullGame"
QT_MOC_LITERAL(16, 170, 7), // "message"
QT_MOC_LITERAL(17, 178, 6), // "theEnd"
QT_MOC_LITERAL(18, 185, 10), // "startRound"
QT_MOC_LITERAL(19, 196, 7), // "letters"
QT_MOC_LITERAL(20, 204, 6), // "rounds"
QT_MOC_LITERAL(21, 211, 9), // "getResult"
QT_MOC_LITERAL(22, 221, 13), // "resultMessage"
QT_MOC_LITERAL(23, 235, 15), // "connectToServer"
QT_MOC_LITERAL(24, 251, 12), // "QHostAddress"
QT_MOC_LITERAL(25, 264, 7), // "address"
QT_MOC_LITERAL(26, 272, 4), // "port"
QT_MOC_LITERAL(27, 277, 5), // "login"
QT_MOC_LITERAL(28, 283, 8), // "userName"
QT_MOC_LITERAL(29, 292, 11), // "sendMessage"
QT_MOC_LITERAL(30, 304, 18), // "disconnectFromHost"
QT_MOC_LITERAL(31, 323, 9), // "startGame"
QT_MOC_LITERAL(32, 333, 11) // "onReadyRead"

    },
    "ChatClient\0connected\0\0loginError\0"
    "reason\0disconnected\0messageReceived\0"
    "text\0error\0QAbstractSocket::SocketError\0"
    "socketError\0userJoined\0username\0"
    "userLeft\0enableGame\0fullGame\0message\0"
    "theEnd\0startRound\0letters\0rounds\0"
    "getResult\0resultMessage\0connectToServer\0"
    "QHostAddress\0address\0port\0login\0"
    "userName\0sendMessage\0disconnectFromHost\0"
    "startGame\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    1,  105,    2, 0x06 /* Public */,
       5,    0,  108,    2, 0x06 /* Public */,
       6,    1,  109,    2, 0x06 /* Public */,
       8,    1,  112,    2, 0x06 /* Public */,
      11,    1,  115,    2, 0x06 /* Public */,
      13,    1,  118,    2, 0x06 /* Public */,
      14,    0,  121,    2, 0x06 /* Public */,
      15,    1,  122,    2, 0x06 /* Public */,
      17,    1,  125,    2, 0x06 /* Public */,
      18,    2,  128,    2, 0x06 /* Public */,
      21,    1,  133,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    2,  136,    2, 0x0a /* Public */,
      27,    1,  141,    2, 0x0a /* Public */,
      29,    1,  144,    2, 0x0a /* Public */,
      30,    0,  147,    2, 0x0a /* Public */,
      31,    0,  148,    2, 0x0a /* Public */,
      32,    0,  149,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   19,   20,
    QMetaType::Void, QMetaType::QString,   22,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 24, QMetaType::UShort,   25,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ChatClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChatClient *_t = static_cast<ChatClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->loginError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->disconnected(); break;
        case 3: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->userJoined((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->userLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->enableGame(); break;
        case 8: _t->fullGame((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->theEnd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->startRound((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 11: _t->getResult((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->connectToServer((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 13: _t->login((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->disconnectFromHost(); break;
        case 16: _t->startGame(); break;
        case 17: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ChatClient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::loginError)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::disconnected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::messageReceived)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::error)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::userJoined)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::userLeft)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::enableGame)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::fullGame)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::theEnd)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & , const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::startRound)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (ChatClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::getResult)) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject ChatClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ChatClient.data,
      qt_meta_data_ChatClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ChatClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ChatClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ChatClient::loginError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChatClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ChatClient::messageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ChatClient::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatClient::userJoined(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatClient::userLeft(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ChatClient::enableGame()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void ChatClient::fullGame(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ChatClient::theEnd(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ChatClient::startRound(const QString & _t1, const int & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ChatClient::getResult(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
