/****************************************************************************
** Meta object code from reading C++ file 'myWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "myWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myWindow_t {
    QByteArrayData data[11];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myWindow_t qt_meta_stringdata_myWindow = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myWindow"
QT_MOC_LITERAL(1, 9, 16), // "OnSliderMoved_M1"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 1), // "i"
QT_MOC_LITERAL(4, 29, 16), // "OnSliderMoved_M2"
QT_MOC_LITERAL(5, 46, 20), // "OnCheckboxClicked_M1"
QT_MOC_LITERAL(6, 67, 5), // "state"
QT_MOC_LITERAL(7, 73, 20), // "OnCheckboxClicked_M2"
QT_MOC_LITERAL(8, 94, 21), // "OnDirectionChanged_M1"
QT_MOC_LITERAL(9, 116, 5), // "index"
QT_MOC_LITERAL(10, 122, 21) // "OnDirectionChanged_M2"

    },
    "myWindow\0OnSliderMoved_M1\0\0i\0"
    "OnSliderMoved_M2\0OnCheckboxClicked_M1\0"
    "state\0OnCheckboxClicked_M2\0"
    "OnDirectionChanged_M1\0index\0"
    "OnDirectionChanged_M2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    1,   47,    2, 0x0a /* Public */,
       5,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
      10,    1,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void myWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnSliderMoved_M1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnSliderMoved_M2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnCheckboxClicked_M1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnCheckboxClicked_M2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnDirectionChanged_M1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->OnDirectionChanged_M2((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_myWindow.data,
    qt_meta_data_myWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int myWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
