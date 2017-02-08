/****************************************************************************
** Meta object code from reading C++ file 'backupitemwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../utilities/tests/qt-configManagerProto/Views/backupitemwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backupitemwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BackupItemWidget_t {
    QByteArrayData data[7];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackupItemWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackupItemWidget_t qt_meta_stringdata_BackupItemWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "BackupItemWidget"
QT_MOC_LITERAL(1, 17, 10), // "droppedOut"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "QDropEvent*"
QT_MOC_LITERAL(4, 41, 7), // "Backup*"
QT_MOC_LITERAL(5, 49, 22), // "on_trashButton_pressed"
QT_MOC_LITERAL(6, 72, 24) // "on_decryptButton_pressed"

    },
    "BackupItemWidget\0droppedOut\0\0QDropEvent*\0"
    "Backup*\0on_trashButton_pressed\0"
    "on_decryptButton_pressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackupItemWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   34,    2, 0x09 /* Protected */,
       6,    0,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BackupItemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackupItemWidget *_t = static_cast<BackupItemWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->droppedOut((*reinterpret_cast< QDropEvent*(*)>(_a[1])),(*reinterpret_cast< Backup*(*)>(_a[2]))); break;
        case 1: _t->on_trashButton_pressed(); break;
        case 2: _t->on_decryptButton_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BackupItemWidget::*_t)(QDropEvent * , Backup * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BackupItemWidget::droppedOut)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject BackupItemWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BackupItemWidget.data,
      qt_meta_data_BackupItemWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BackupItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackupItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BackupItemWidget.stringdata0))
        return static_cast<void*>(const_cast< BackupItemWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BackupItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BackupItemWidget::droppedOut(QDropEvent * _t1, Backup * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
