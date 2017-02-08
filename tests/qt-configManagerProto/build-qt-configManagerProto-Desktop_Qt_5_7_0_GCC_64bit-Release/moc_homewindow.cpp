/****************************************************************************
** Meta object code from reading C++ file 'homewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../utilities/tests/qt-configManagerProto/Views/homewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HomeWindow_t {
    QByteArrayData data[14];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HomeWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HomeWindow_t qt_meta_stringdata_HomeWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HomeWindow"
QT_MOC_LITERAL(1, 11, 13), // "cryptingStart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "Backup*"
QT_MOC_LITERAL(4, 34, 12), // "cryptingDone"
QT_MOC_LITERAL(5, 47, 26), // "on_newBackupButton_clicked"
QT_MOC_LITERAL(6, 74, 22), // "on_actionRAZ_triggered"
QT_MOC_LITERAL(7, 97, 30), // "on_actionUtilisateur_triggered"
QT_MOC_LITERAL(8, 128, 19), // "onBackupItemClicked"
QT_MOC_LITERAL(9, 148, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(10, 165, 16), // "cryptingProgress"
QT_MOC_LITERAL(11, 182, 15), // "onCryptingStart"
QT_MOC_LITERAL(12, 198, 14), // "onCryptingDone"
QT_MOC_LITERAL(13, 213, 26) // "on_action_propos_triggered"

    },
    "HomeWindow\0cryptingStart\0\0Backup*\0"
    "cryptingDone\0on_newBackupButton_clicked\0"
    "on_actionRAZ_triggered\0"
    "on_actionUtilisateur_triggered\0"
    "onBackupItemClicked\0QListWidgetItem*\0"
    "cryptingProgress\0onCryptingStart\0"
    "onCryptingDone\0on_action_propos_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomeWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   68,    2, 0x09 /* Protected */,
       6,    0,   69,    2, 0x09 /* Protected */,
       7,    0,   70,    2, 0x09 /* Protected */,
       8,    1,   71,    2, 0x09 /* Protected */,
      10,    2,   74,    2, 0x09 /* Protected */,
      11,    1,   79,    2, 0x09 /* Protected */,
      12,    0,   82,    2, 0x09 /* Protected */,
      13,    0,   83,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Bool, 0x80000000 | 3,    2,
    QMetaType::Bool,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HomeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HomeWindow *_t = static_cast<HomeWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->cryptingStart((*reinterpret_cast< Backup*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->cryptingDone();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->on_newBackupButton_clicked(); break;
        case 3: _t->on_actionRAZ_triggered(); break;
        case 4: _t->on_actionUtilisateur_triggered(); break;
        case 5: _t->onBackupItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->cryptingProgress((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 7: _t->onCryptingStart((*reinterpret_cast< Backup*(*)>(_a[1]))); break;
        case 8: _t->onCryptingDone(); break;
        case 9: _t->on_action_propos_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef bool (HomeWindow::*_t)(Backup * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HomeWindow::cryptingStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef bool (HomeWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HomeWindow::cryptingDone)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject HomeWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_HomeWindow.data,
      qt_meta_data_HomeWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HomeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HomeWindow.stringdata0))
        return static_cast<void*>(const_cast< HomeWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int HomeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
bool HomeWindow::cryptingStart(Backup * _t1)
{
    bool _t0 = bool();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
bool HomeWindow::cryptingDone()
{
    bool _t0 = bool();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
