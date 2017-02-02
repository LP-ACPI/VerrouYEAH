/****************************************************************************
** Meta object code from reading C++ file 'ftp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt-pseudoftp/ftp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Ftp_t {
    QByteArrayData data[16];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ftp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ftp_t qt_meta_stringdata_Ftp = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Ftp"
QT_MOC_LITERAL(1, 4, 8), // "finished"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 5), // "error"
QT_MOC_LITERAL(4, 20, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(5, 48, 25), // "on_transferButton_clicked"
QT_MOC_LITERAL(6, 74, 16), // "on_returnPressed"
QT_MOC_LITERAL(7, 91, 23), // "on_uploadChoice_clicked"
QT_MOC_LITERAL(8, 115, 25), // "on_downloadChoice_clicked"
QT_MOC_LITERAL(9, 141, 21), // "on_quitButton_clicked"
QT_MOC_LITERAL(10, 163, 10), // "openDialog"
QT_MOC_LITERAL(11, 174, 12), // "ftpReadyRead"
QT_MOC_LITERAL(12, 187, 16), // "uploadInProgress"
QT_MOC_LITERAL(13, 204, 18), // "downloadInProgress"
QT_MOC_LITERAL(14, 223, 15), // "requestFinished"
QT_MOC_LITERAL(15, 239, 12) // "requestError"

    },
    "Ftp\0finished\0\0error\0QNetworkReply::NetworkError\0"
    "on_transferButton_clicked\0on_returnPressed\0"
    "on_uploadChoice_clicked\0"
    "on_downloadChoice_clicked\0"
    "on_quitButton_clicked\0openDialog\0"
    "ftpReadyRead\0uploadInProgress\0"
    "downloadInProgress\0requestFinished\0"
    "requestError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ftp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   83,    2, 0x09 /* Protected */,
       6,    0,   84,    2, 0x09 /* Protected */,
       7,    0,   85,    2, 0x09 /* Protected */,
       8,    0,   86,    2, 0x09 /* Protected */,
       9,    0,   87,    2, 0x09 /* Protected */,
      10,    0,   88,    2, 0x09 /* Protected */,
      11,    0,   89,    2, 0x09 /* Protected */,
      12,    2,   90,    2, 0x09 /* Protected */,
      13,    2,   95,    2, 0x09 /* Protected */,
      14,    0,  100,    2, 0x09 /* Protected */,
      15,    1,  101,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void Ftp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ftp *_t = static_cast<Ftp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 2: _t->on_transferButton_clicked(); break;
        case 3: _t->on_returnPressed(); break;
        case 4: _t->on_uploadChoice_clicked(); break;
        case 5: _t->on_downloadChoice_clicked(); break;
        case 6: _t->on_quitButton_clicked(); break;
        case 7: _t->openDialog(); break;
        case 8: _t->ftpReadyRead(); break;
        case 9: _t->uploadInProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 10: _t->downloadInProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 11: _t->requestFinished(); break;
        case 12: _t->requestError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Ftp::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::finished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Ftp::*_t)(QNetworkReply::NetworkError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ftp::error)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Ftp::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Ftp.data,
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
    return QDialog::qt_metacast(_clname);
}

int Ftp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Ftp::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Ftp::error(QNetworkReply::NetworkError _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
