/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[27];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 9), // "connected"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 10), // "loginError"
QT_MOC_LITERAL(4, 29, 6), // "reason"
QT_MOC_LITERAL(5, 36, 12), // "disconnected"
QT_MOC_LITERAL(6, 49, 5), // "error"
QT_MOC_LITERAL(7, 55, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 84, 11), // "socketError"
QT_MOC_LITERAL(9, 96, 8), // "fullGame"
QT_MOC_LITERAL(10, 105, 6), // "theEnd"
QT_MOC_LITERAL(11, 112, 7), // "message"
QT_MOC_LITERAL(12, 120, 10), // "enableGame"
QT_MOC_LITERAL(13, 131, 10), // "startRound"
QT_MOC_LITERAL(14, 142, 9), // "getResult"
QT_MOC_LITERAL(15, 152, 13), // "resultMessage"
QT_MOC_LITERAL(16, 166, 15), // "connectToServer"
QT_MOC_LITERAL(17, 182, 12), // "QHostAddress"
QT_MOC_LITERAL(18, 195, 7), // "address"
QT_MOC_LITERAL(19, 203, 4), // "port"
QT_MOC_LITERAL(20, 208, 5), // "login"
QT_MOC_LITERAL(21, 214, 8), // "userName"
QT_MOC_LITERAL(22, 223, 11), // "sendMessage"
QT_MOC_LITERAL(23, 235, 4), // "text"
QT_MOC_LITERAL(24, 240, 18), // "disconnectFromHost"
QT_MOC_LITERAL(25, 259, 9), // "startGame"
QT_MOC_LITERAL(26, 269, 11) // "onReadyRead"

    },
    "Client\0connected\0\0loginError\0reason\0"
    "disconnected\0error\0QAbstractSocket::SocketError\0"
    "socketError\0fullGame\0theEnd\0message\0"
    "enableGame\0startRound\0getResult\0"
    "resultMessage\0connectToServer\0"
    "QHostAddress\0address\0port\0login\0"
    "userName\0sendMessage\0text\0disconnectFromHost\0"
    "startGame\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    1,   90,    2, 0x06 /* Public */,
       5,    0,   93,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,
       9,    0,   97,    2, 0x06 /* Public */,
      10,    1,   98,    2, 0x06 /* Public */,
      12,    0,  101,    2, 0x06 /* Public */,
      13,    1,  102,    2, 0x06 /* Public */,
      14,    1,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    2,  108,    2, 0x0a /* Public */,
      20,    1,  113,    2, 0x0a /* Public */,
      22,    1,  116,    2, 0x0a /* Public */,
      24,    0,  119,    2, 0x0a /* Public */,
      25,    0,  120,    2, 0x0a /* Public */,
      26,    0,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 17, QMetaType::UShort,   18,   19,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->loginError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->disconnected(); break;
        case 3: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->fullGame(); break;
        case 5: _t->theEnd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->enableGame(); break;
        case 7: _t->startRound((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->getResult((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->connectToServer((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 10: _t->login((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->disconnectFromHost(); break;
        case 13: _t->startGame(); break;
        case 14: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
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
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::loginError)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::disconnected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::error)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::fullGame)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::theEnd)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::enableGame)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::startRound)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::getResult)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Client::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::loginError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Client::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Client::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Client::fullGame()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Client::theEnd(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Client::enableGame()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Client::startRound(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Client::getResult(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
