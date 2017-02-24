/****************************************************************************
** Meta object code from reading C++ file 'Ftp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/services/Ftp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Ftp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ftp_t {
    QByteArrayData data[15];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ftp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ftp_t qt_meta_stringdata_Ftp = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Ftp"
QT_MOC_LITERAL(1, 4, 15), // "downloadStarted"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 13), // "uploadStarted"
QT_MOC_LITERAL(4, 35, 8), // "finished"
QT_MOC_LITERAL(5, 44, 5), // "error"
QT_MOC_LITERAL(6, 50, 16), // "transferProgress"
QT_MOC_LITERAL(7, 67, 12), // "ftpReadyRead"
QT_MOC_LITERAL(8, 80, 18), // "transferInProgress"
QT_MOC_LITERAL(9, 99, 15), // "requestFinished"
QT_MOC_LITERAL(10, 115, 12), // "requestError"
QT_MOC_LITERAL(11, 128, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(12, 156, 9), // "sslErrors"
QT_MOC_LITERAL(13, 166, 16), // "QList<QSslError>"
QT_MOC_LITERAL(14, 183, 13) // "cancelTranfer"

    },
    "Ftp\0downloadStarted\0\0uploadStarted\0"
    "finished\0error\0transferProgress\0"
    "ftpReadyRead\0transferInProgress\0"
    "requestFinished\0requestError\0"
    "QNetworkReply::NetworkError\0sslErrors\0"
    "QList<QSslError>\0cancelTranfer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ftp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       6,    2,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   80,    2, 0x08 /* Private */,
       8,    2,   81,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    1,   87,    2, 0x08 /* Private */,
      12,    1,   90,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Ftp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ftp *_t = static_cast<Ftp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadStarted(); break;
        case 1: _t->uploadStarted(); break;
        case 2: _t->finished(); break;
        case 3: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->transferProgress((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 5: _t->ftpReadyRead(); break;
        case 6: _t->transferInProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->requestFinished(); break;
        case 8: _t->requestError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 9: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 10: _t->cancelTranfer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Ftp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::downloadStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Ftp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::uploadStarted)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Ftp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::finished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Ftp::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::error)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Ftp::*_t)(quint64 , quint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::transferProgress)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Ftp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Ftp.data,
      qt_meta_data_Ftp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Ftp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ftp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Ftp.stringdata0))
        return static_cast<void*>(const_cast< Ftp*>(this));
    return QObject::qt_metacast(_clname);
}

int Ftp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Ftp::downloadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Ftp::uploadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Ftp::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Ftp::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Ftp::transferProgress(quint64 _t1, quint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
