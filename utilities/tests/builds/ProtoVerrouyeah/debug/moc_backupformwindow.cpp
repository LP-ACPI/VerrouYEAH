/****************************************************************************
** Meta object code from reading C++ file 'backupformwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qt-configManagerProto/Views/backupformwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backupformwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BackupFormWindow_t {
    QByteArrayData data[6];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackupFormWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackupFormWindow_t qt_meta_stringdata_BackupFormWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "BackupFormWindow"
QT_MOC_LITERAL(1, 17, 30), // "on_newBackupButtonBox_accepted"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 30), // "on_newBackupButtonBox_rejected"
QT_MOC_LITERAL(4, 80, 23), // "on_srcDirChoose_clicked"
QT_MOC_LITERAL(5, 104, 23) // "on_trgDirChoose_clicked"

    },
    "BackupFormWindow\0on_newBackupButtonBox_accepted\0"
    "\0on_newBackupButtonBox_rejected\0"
    "on_srcDirChoose_clicked\0on_trgDirChoose_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackupFormWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x09 /* Protected */,
       3,    0,   35,    2, 0x09 /* Protected */,
       4,    0,   36,    2, 0x09 /* Protected */,
       5,    0,   37,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BackupFormWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackupFormWindow *_t = static_cast<BackupFormWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_newBackupButtonBox_accepted(); break;
        case 1: _t->on_newBackupButtonBox_rejected(); break;
        case 2: _t->on_srcDirChoose_clicked(); break;
        case 3: _t->on_trgDirChoose_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject BackupFormWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BackupFormWindow.data,
      qt_meta_data_BackupFormWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BackupFormWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackupFormWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BackupFormWindow.stringdata0))
        return static_cast<void*>(const_cast< BackupFormWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int BackupFormWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
